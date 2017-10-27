/*
 *  COPYRIGHT NOTICE
 *  Copyright (c) 2016, Wuhan Douyu Network Technology Co., Ltd.
 *  All rights reserved.
 *
 *  @version : 1.0
 *  @author : mxl
 *  @E-mail : xiaolongicx@gmail.com
 *  @date : Thu Feb 28 10:30:20 CST 2017
 *
 *  Revision Notes :
 */

#include <RedisDB/RedisDB.h>
#include <RedisDB/SttRedisContainers.h>
#include <SttMongoDB/SttMongoDB.h>
#include <boost/foreach.hpp>
#include <Common/Tools.h>
#include <netmsg/common_const_def.h>
#include <dylog/dy_log.h>
#include "MailMigrator.h"
#include "MailDAO.h"
#include "cfg.h"

static const std::string gen_key_for_uid(int32_t uid)
{
    char key_name[64] = {0};
    snprintf(key_name, sizeof(key_name), "%d", uid / 1000000);

    return key_name;
}

MailMigrator::MailMigrator(MailConfig *cfg)
    :_old_mongo_host(cfg->old_system_mongo_dao_host.c_str()),
    _old_mongo_port(cfg->old_system_mongo_dao_port),
    _migrated_list_redis_host(cfg->migrate_redis_host.c_str()),
    _migrated_list_redis_port(cfg->migrate_redis_port),
    _migrated_list_redis_prefix(cfg->migrate_redis_prefix.c_str()),
    _migrated_uid_set(),
    _migrate_uid_set_lock(),
    _migrated_user_count(0),
    _migrated_failed_count(0)
{
    BOOST_FOREACH(const MailConfig::TitleMidPair &tm_pair, cfg->title_mailid_arr)
    {
        _batch_mail_map[tm_pair.first] = tm_pair.second;
    }

    _redis_pool = new RedisDBPool(_migrated_list_redis_host.c_str(), _migrated_list_redis_port, _migrated_list_redis_prefix.c_str());
    _old_system_mongo_pool = new MongoDBPool(_old_mongo_host.c_str(), _old_mongo_port);

    _user_mail_dao = new UserMailMongoDAO(cfg->new_system_mongo_dao_host.c_str(), cfg->new_system_mongo_dao_port);
}

bool MailMigrator::try_migrate(int32_t uid)
{
    {
        CSttAutoLock gate(_migrate_uid_set_lock);
        if (_migrated_uid_set.count(uid) > 0)
        {
            //DY_DEBUG_LOG(uid, "", "", " %d already migrated judge locally ", uid);

            return true;
        }
    }

    std::string err_info;
    SttRedisDB *redis = _redis_pool->GetConnection(err_info);
    if (!redis)
    {
        DY_ERROR_LOG(ET_DB_CONNECTION_ERR, 0, "", "", " connect %s:%d failed as %s ",
            _migrated_list_redis_host.c_str(), _migrated_list_redis_port, err_info.c_str());

        return false;
    }

    bool ret = true;
    do
    {
        RedisContainer::Set redis_set;
        if( !redis_set.attachRedisDB(redis) )
        {
            DY_ERROR_LOG(ET_DB_CONNECTION_ERR, 0, "", "", "attach redis %s:%d failed.", _migrated_list_redis_host.c_str(), _migrated_list_redis_port);

            ret = false;
            break;
        }

        if (redis_set.ismember(gen_key_for_uid(uid).c_str(), convertToString(uid).c_str()))
        {
            //DY_DEBUG_LOG(uid, "", "", " %d already migrated ", uid);
            {
                CSttAutoLock gate(_migrate_uid_set_lock);
                _migrated_uid_set.insert(uid);
            }

            break;
        }
        else
        {
            ret = migrate_impl(uid);
            if (ret)
            {
                redis_set.add(gen_key_for_uid(uid).c_str(), convertToString(uid).c_str());

                {
                    CSttAutoLock gate(_migrate_uid_set_lock);
                    _migrated_uid_set.insert(uid);
                }

                //notify_old_system(uid);

                //DY_DEBUG_LOG(uid, "", "", " %d migrate successfully ", uid);
                ++_migrated_user_count;
            }
            else
            {
                DY_ERROR_LOG(ET_UNKNOWN, uid, "", "", " %d migrate failed ", uid);
                ++_migrated_failed_count;
            }
        }
    } while (0);

    _redis_pool->ReleaseConnection(redis);
    //redis.Close();
    return ret;
}

bool MailMigrator::migrate_impl(int32_t uid) const
{
    UserMailWrapArray user_mail_arr;
    // read from old system
    if (!get_mail_from_old_system(uid, user_mail_arr))
    {
        return false;
    }

    filter_dirty_mail(user_mail_arr);

    // write to new system
    if (!set_mail_to_new_system(uid, user_mail_arr))
    {
        return false;
    }

    return true;
}

bool MailMigrator::get_mail_from_old_system(int32_t uid, UserMailWrapArray &arr) const
{
    arr.clear();

    std::string err_info;
    SttMongoDB *mongo = _old_system_mongo_pool->GetConnection(err_info);
    if (!mongo)
    {
        DY_ERROR_LOG(ET_DB_CONNECTION_ERR, uid, "", "", "connect %s:%d failed.", _old_mongo_host.c_str(), _old_mongo_port);

        return false;
    }

    bool ret = true;
    do
    {
        std::string ret_str;
        char query_json[1024] = {0};
        snprintf(query_json, sizeof(query_json), "{\"dst_id\": %d, \"status\": {$ne: %d}, \"mt\": {$ne: %d}}", uid, MS_DELETE, 1);

        if (!mongo->QueryDoc(ret_str, "innermail", "summary", query_json, err_info))
        {
            DY_ERROR_LOG(ET_DB_QUERY_ERR, uid, "", "", "query by %s error %s", query_json, err_info.c_str());

            ret = false;
            break;
        }

        MultiUserMailArray multi_arr;
        if(!json_array_old_format_to_user_mail_wrap_array(ret_str.c_str(), multi_arr))
        {
            DY_ERROR_LOG(ET_DB_QUERY_ERR, uid, "", "", "MailMigrator::get_mail_from_old_system %s json_format error ", ret_str.c_str());

            ret = false;
            break;
        }

        BOOST_FOREACH(const UserMailArray &user_mail_arr, multi_arr)
        {
            if (user_mail_arr.uid == uid)
            {
                arr.reserve(user_mail_arr.unread_mail_arr.size() + user_mail_arr.read_mail_arr.size());

                arr.insert(arr.end(), user_mail_arr.unread_mail_arr.begin(), user_mail_arr.unread_mail_arr.end());
                arr.insert(arr.end(), user_mail_arr.read_mail_arr.begin(), user_mail_arr.read_mail_arr.end());

                break;
            }
        }
    } while (0);

    _old_system_mongo_pool->ReleaseConnection(mongo);
    return ret;
}

bool MailMigrator::set_mail_to_new_system(int32_t uid, const UserMailWrapArray &arr) const
{
    UserMailWrapArray batch_arr;
    UserMailWrapArray no_batch_arr;

    batch_nobatch_split(arr, batch_arr, no_batch_arr);

    std::sort(batch_arr.begin(), batch_arr.end(), mail_ts_less);
    if(!_user_mail_dao->migrate_user_mail(uid, batch_arr, true))
    {
        return false;
    }

    std::sort(no_batch_arr.begin(), no_batch_arr.end(), mail_ts_less);
    if (!_user_mail_dao->migrate_user_mail(uid, no_batch_arr))
    {
        return false;
    }

    return true;
}

void MailMigrator::batch_nobatch_split(const UserMailWrapArray &arr, UserMailWrapArray &batch_arr, UserMailWrapArray &no_batch_arr) const
{
    batch_arr.clear();
    no_batch_arr.clear();

    std::set<std::string> batch_mid_set;

    BOOST_FOREACH(const UserMailWrap &mail, arr)
    {
        TitleMidMapConstIterator cit = _batch_mail_map.find(mail.title);
        if (cit != _batch_mail_map.end())
        {
            UserMailWrap batch_mail;
            batch_mail.mid = cit->second;
            batch_mail.status = mail.status;

            if (batch_mid_set.count(batch_mail.mid) > 0)
            {
                continue;;
            }
            else
            {
                batch_mid_set.insert(batch_mail.mid);
            }

            batch_arr.push_back(batch_mail);
        }
        else
        {
            no_batch_arr.push_back(mail);
        }
    }
}

void MailMigrator::filter_dirty_mail(UserMailWrapArray &arr) const
{
    UserMailWrapArray::iterator it = arr.begin();
    while(it != arr.end())
    {
        if (it->title == "我在鱼吧关注了你")
        {
            it = arr.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void MailMigrator::show_status() const
{
    std::cout << _migrated_user_count << " users has beed migrated" << std::endl;
    std::cout << _migrated_failed_count << " users failed to migrated" << std::endl;
}

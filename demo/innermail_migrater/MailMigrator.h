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

#ifndef __MAIL_MIGRATOR_H__
#define __MAIL_MIGRATOR_H__

#include <map>
#include <string>
#include <stdint.h>
#include <rpclib/BatchMailServerRPCLib.h>
#include <RedisDB/RedisDBPool.h>
#include <boost/unordered_set.hpp>
#include <CommonBase/ThreadTool.h>
#include <SttMongoDB/MongoDBPool.h>
#include "data_def.h"

class UserMailMongoDAO;
struct MailConfig;

class MailMigrator
{
public:
    MailMigrator(MailConfig *cfg);
    ~MailMigrator()
    {
        delete _old_system_mongo_pool;
        delete _redis_pool;
    }

    bool try_migrate(int32_t uid);
    void show_status() const;

protected:
    bool migrate_impl(int32_t uid) const;

    bool get_mail_from_old_system(int32_t uid, UserMailWrapArray &arr) const;
    bool set_mail_to_new_system(int32_t uid, const UserMailWrapArray &arr) const;
    void filter_dirty_mail(UserMailWrapArray &arr) const;

    void batch_nobatch_split(const UserMailWrapArray &arr, UserMailWrapArray &batch_arr, UserMailWrapArray &no_batch_arr) const;

protected:
    UserMailMongoDAO *_user_mail_dao;

    std::string _old_mongo_host;
    uint16_t _old_mongo_port;

    std::string _migrated_list_redis_host;
    uint16_t _migrated_list_redis_port;
    std::string _migrated_list_redis_prefix;

    typedef std::map<std::string, std::string> TitleMidMap;
    typedef TitleMidMap::const_iterator TitleMidMapConstIterator;
    TitleMidMap _batch_mail_map;
    RedisDBPool *_redis_pool;

    boost::unordered_set<int32_t> _migrated_uid_set;
    CSttLockCS _migrate_uid_set_lock;

    MongoDBPool *_old_system_mongo_pool;

    int32_t _migrated_user_count;
    int32_t _migrated_failed_count;
};

 #endif //__MAIL_MIGRATOR_H__

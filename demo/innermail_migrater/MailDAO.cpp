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

#include <netmsg/common_const_def.h>
#include <dylog/dy_log.h>
#include "MailDAO.h"

bool UserMailMongoDAO::migrate_user_mail(int32_t uid, const UserMailWrapArray &user_mail_wrap_arr, bool is_batch /*= false*/) const
{
    std::string err_info;
    SttMongoDB *mongo = _db_pool->GetConnection(err_info);
    if (!mongo)
    {
        DY_ERROR_LOG(ET_DB_CONNECTION_ERR, uid, "", "", " connect %s:%d failed as %s ", _host.c_str(), _port, err_info.c_str());

        return false;
    }

    char condition_json[64] = {0};
    snprintf(condition_json, sizeof(condition_json), "{\"uid\": %d}", uid);

    bool ret = true;
    do
    {
        if (user_mail_wrap_arr.empty())
        {
            std::string update_json = "{$addToSet: {\"unread_mails\": {$each: []}}, $addToSet: {\"read_mails\": {$each: []}}, $addToSet: {\"del_mails\": {$each: []}}}";

            if (!mongo->UpdateDoc(DB_NAME(), COLLECTION_NAME(), condition_json, update_json.c_str(), err_info, true))
            {
                DY_ERROR_LOG(ET_DB_QUERY_ERR, uid, "", "", "update %s : %s error %s",
                    condition_json, update_json.c_str(), err_info.c_str());

                ret = false;
                break;
            }
        }
        else
        {
            std::string update_json = "{";

            bool have_unread = false;
            std::string unread_update_json = "$push: {\"unread_mails\": {$each: [";

            bool have_read = false;
            std::string read_update_json = "$push: {\"read_mails\": {$each: [";

            bool is_unread_first = true;
            bool is_read_first = true;
            BOOST_FOREACH(const UserMailWrap &user_mail_wrap, user_mail_wrap_arr)
            {
                if (user_mail_wrap.status == MS_UNREAD)
                {
                    if (!is_unread_first)
                    {
                        unread_update_json += ", ";
                    }
                    else
                    {
                        is_unread_first = false;
                    }

                    unread_update_json += user_mail_wrap.to_json(is_batch);
                    have_unread = true;
                }
                else if (user_mail_wrap.status == MS_READ)
                {
                    if (!is_read_first)
                    {
                        read_update_json += ", ";
                    }
                    else
                    {
                        is_read_first = false;
                    }

                    read_update_json += user_mail_wrap.to_json(is_batch);
                    have_read = true;
                }
            }

            if (have_unread)
            {
                update_json += unread_update_json;
                update_json += "], $sort: {ts: 1}}}";
            }

            if (have_read)
            {
                if (have_unread)
                {
                    update_json += ", ";
                }

                update_json += read_update_json;
                update_json += "], $sort: {ts: 1}}}";
            }

            update_json += "}";

            if (!mongo->UpdateDoc(DB_NAME(), COLLECTION_NAME(), condition_json, update_json.c_str(), err_info, true))
            {
                DY_ERROR_LOG(ET_DB_QUERY_ERR, uid, "", "", " update %s : %s error %s ",
                    condition_json, update_json.c_str(), err_info.c_str());

                ret = false;
                break;
            }
        }
    } while (0);

    _db_pool->ReleaseConnection(mongo);
    return ret;
}

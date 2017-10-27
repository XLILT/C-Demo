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

#ifndef __MAIL_DAO_H__
#define __MAIL_DAO_H__

#include <stdint.h>
#include <SttMongoDB/MongoDBPool.h>
#include <RedisDB/RedisDBPool.h>
#include "data_def.h"

class UserMailMongoDAO
{
public:
    UserMailMongoDAO(const char *host, uint16_t port)
        :_host(host),
        _port(port)
    {
        _db_pool = new MongoDBPool(_host.c_str(), _port);
    }

    ~UserMailMongoDAO()
    {
        delete _db_pool;
    }

    static const uint32_t MISSING_REPRESENTATIVE_COUNT = 0x7FFFFFFF;  //doc miss

    static const char * DB_NAME() { return "user_batch_mail"; }
    static const char * COLLECTION_NAME() { return "summary"; }

    bool migrate_user_mail(int32_t uid, const UserMailWrapArray &user_mail_wrap_arr, bool is_batch = false) const;

protected:
    std::string _host;
    uint16_t _port;

    MongoDBPool *_db_pool;
};

#endif  //__MAIL_DAO_H__

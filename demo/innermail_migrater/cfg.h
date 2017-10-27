/*
 *  COPYRIGHT NOTICE
 *  Copyright (c) 2016, Wuhan Douyu Network Technology Co., Ltd.
 *  All rights reserved.
 *
 *  @version : 1.0
 *  @author : mxl
 *  @E-mail : xiaolongicx@gmail.com
 *  @date : Thu Feb 28 13:20:20 CST 2017
 *
 *  Revision Notes :
 */

#ifndef __CFG_H__
#define __CFG_H__

#include <stdint.h>
#include <fstream>

struct MailConfig
{
    typedef std::pair<std::string, std::string> TitleMidPair;
    typedef std::vector<TitleMidPair> TitleMidPairArray;

    std::string old_system_mongo_dao_host;
    uint16_t old_system_mongo_dao_port;

    std::string new_system_mongo_dao_host;
    uint16_t new_system_mongo_dao_port;

    std::string migrate_redis_host;
    uint16_t migrate_redis_port;
    std::string migrate_redis_prefix;

    TitleMidPairArray title_mailid_arr;

    int32_t begin_uid;
    int32_t end_uid;

    MailConfig() :
        old_system_mongo_dao_host(),
        old_system_mongo_dao_port(0),
        new_system_mongo_dao_host(),
        new_system_mongo_dao_port(0),
        migrate_redis_host(),
        migrate_redis_port(0),
        migrate_redis_prefix(),
        title_mailid_arr(),
        begin_uid(0),
        end_uid(0)
    {}

    static const char * file_name()
    {
        return "config.json";
    }

    bool load_cfg()
    {
        std::ifstream ifs(file_name());
        std::string all_str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

        ifs.close();

        Json::Value config_root;
        Json::Reader r;

        if(!r.parse(all_str, config_root))
        {
            return false;
        }

        if(!config_root.isObject())
        {
            return false;
        }

        if(config_root["OldSystemMongoHost"].isNull() || !config_root["OldSystemMongoHost"].isString())
        {
            return false;
        }

        if(config_root["OldSystemMongoPort"].isNull() || !config_root["OldSystemMongoPort"].isInt())
        {
            return false;
        }

        if(config_root["UserMailMongoHost"].isNull() || !config_root["UserMailMongoHost"].isString())
        {
            return false;
        }

        if(config_root["UserMailMongoPort"].isNull() || !config_root["UserMailMongoPort"].isInt())
        {
            return false;
        }

        if(config_root["MigrateRedisHost"].isNull() || !config_root["MigrateRedisHost"].isString())
        {
            return false;
        }

        if(config_root["MigrateRedisPort"].isNull() || !config_root["MigrateRedisPort"].isInt())
        {
            return false;
        }

        if(config_root["MigrateRedisPrefix"].isNull() || !config_root["MigrateRedisPrefix"].isString())
        {
            return false;
        }

        if(config_root["BeginUid"].isNull() || !config_root["BeginUid"].isInt())
        {
            return false;
        }

        if(config_root["EndUid"].isNull() || !config_root["EndUid"].isInt())
        {
            return false;
        }

        old_system_mongo_dao_host = config_root["OldSystemMongoHost"].asCString();
        old_system_mongo_dao_port = config_root["OldSystemMongoPort"].asInt();

        new_system_mongo_dao_host = config_root["UserMailMongoHost"].asCString();
        new_system_mongo_dao_port = config_root["UserMailMongoPort"].asInt();

        migrate_redis_host = config_root["MigrateRedisHost"].asCString();
        migrate_redis_port = config_root["MigrateRedisPort"].asInt();
        migrate_redis_prefix = config_root["MigrateRedisPrefix"].asCString();

        begin_uid = config_root["BeginUid"].asInt();
        end_uid = config_root["EndUid"].asInt();

        const Json::Value &title_mid_arr = config_root["TitleMidArray"];
        if (!title_mid_arr.isNull() && title_mid_arr.isArray())
        {
            for (int i = 0; i < title_mid_arr.size(); ++i)
            {
                const Json::Value &title_mid = title_mid_arr[i];
                if (title_mid.isArray() && title_mid.size() == 2)
                {
                    int title_index = 0;
                    int mid_index = 1;
                    if (title_mid[title_index].isString() && title_mid[mid_index].isString())
                    {
                        title_mailid_arr.push_back(std::make_pair(title_mid[title_index].asCString(), title_mid[mid_index].asCString()));
                    }
                }
            }
        }

        return true;
    }
};

#endif  //__CFG_H__

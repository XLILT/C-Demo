#include "stdafx.h"
#include <SttMongoDB/SttMongoDB.h>

void test_push_efficiency()
{
    SttMongoDB mongodb;
    mongodb.Connect("10.1.141.41", 27027);

    char condition_json[64] = {0};
    snprintf(condition_json, sizeof(condition_json), "{\"uid\": {$in: [1, 2, 3]}}}");

    for (int i = 0; i < 10000; ++i)
    {
        std::string update_json = "{$push: {\"mails\": ";
        update_json += "{\"mid\": \"";
        update_json += convertToString(i);
        update_json += "\", \"status\": 0}";
        update_json += "}}";

        uint64_t start_us = SttGetUsTickCount();
        std::string err_info;
        bool ret = mongodb.UpdateDoc("mytest", "demo", condition_json, update_json.c_str(), err_info, false, true);
        TL_FAST_LOG("cost.log", tlstNoSplit, "cost %luus", SttGetUsTickCount() - start_us);
        if(false == ret)
        {
            TL_FAST_LOG("err.log", tlstNoSplit, "failed %s", err_info.c_str());
        }
    }
}

void test_push_efficiency2()
{
    SttMongoDB mongodb;
    mongodb.Connect("10.1.141.41", 27027);

    char condition_json[64] = {0};
    snprintf(condition_json, sizeof(condition_json), "{\"uid\": {$in: [4, 5, 6]}}}");

    for (int i = 0; i < 10000; ++i)
    {
        std::string update_json = "{$push: {\"mails\": ";
        update_json += "{\"mid\": \"";
        update_json += convertToString(i);
        update_json += "\", \"status\": \"12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\" }";
        update_json += "}}";

        uint64_t start_us = SttGetUsTickCount();
        std::string err_info;
        bool ret = mongodb.UpdateDoc("mytest", "demo", condition_json, update_json.c_str(), err_info, false, true);
        TL_FAST_LOG("cost.log", tlstNoSplit, "cost %luus", SttGetUsTickCount() - start_us);
        if(false == ret)
        {
            TL_FAST_LOG("err.log", tlstNoSplit, "failed %s", err_info.c_str());
        }
    }
}

int main(int argc, char **argv)
{
    test_push_efficiency2();

    TL_SHUTDOWN();
    return 0;
}

#include "stdafx.h"
#include <stdlib.h>
#include <SttMongoDB/SttMongoDB.h>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/detail/atomic_count.hpp>

void update()
{
    SttMongoDB mongodb;
    mongodb.Connect("10.1.141.41", 27027);

    char condition_json[64] = {0};
    snprintf(condition_json, sizeof(condition_json), "{\"uid\": {$in: [1, 2, 3]}}}");

    std::string update_json = "{$push: {\"mails\": ";
    update_json += "{\"mid\": \"2\", \"status\": 0}";
    update_json += "}}";

    std::string err_info;
    bool ret = mongodb.UpdateDoc("mytest", "demo", condition_json, update_json.c_str(), err_info, true, false);

    if(false == ret)
    {
        TL_FAST_LOG("err.log", tlstNoSplit, "failed %s", err_info.c_str());
    }
}

void update2()
{
    SttMongoDB mongodb;
    mongodb.Connect("10.1.141.41", 27017);

    char condition_json[1024] = {0};
    snprintf(condition_json, sizeof(condition_json), "{\"uid\": %d, \"mails.mid\": \"%s\"}", 1, "2");

    char update_json[64] = {0};
    snprintf(update_json, sizeof(condition_json), "{$set: {\"mails.$.status\": %d}}", 0);

    std::string err_info;
    bool ret = mongodb.UpdateDoc("test", "demo", condition_json, update_json, err_info, true);

    if(false == ret)
    {
        TL_FAST_LOG("err.log", tlstNoSplit, "failed %s", err_info.c_str());
    }
}

void aggregate()
{
    SttMongoDB mongodb;
    mongodb.Connect("192.168.1.62", 27027);

    char pipe_json[1024] = {0};
    snprintf(pipe_json, sizeof(pipe_json), "[{$match: {\"uid\": %d}}, {$project: {unread_count: {$size: \"$mails\"}}}]", 21290);

    char aggreate_json[64] = {0};
    snprintf(aggreate_json, sizeof(aggreate_json), "{$match: {\"uid\": %d}}", 21290);

    std::string ret_str;
    std::string err_info;
    bool ret = mongodb.Aggregate(ret_str, "user_batch_mail", "summary", pipe_json, err_info);

    if(false == ret)
    {
        //TL_FAST_LOG("err.log", tlstNoSplit, "failed %s", err_info.c_str());

        std::cout << "error: " << err_info << std::endl;
    }

    std::cout << "ret_str: " << ret_str << std::endl;
}

int main(int argc, char **argv)
{
    //update();
    //update2();
    aggregate();

    return 0;
}

#include "stdafx.h"
#include <stdlib.h>
#include <SttMongoDB/SttMongoDB.h>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/detail/atomic_count.hpp>

boost::detail::atomic_count atom_count(0);

std::string uuid(uint32_t ts)
{
    uint8_t uuid_tmp[12];
    uint64_t count = ++atom_count;
    char str_result[33];
    memcpy(uuid_tmp, &count, 8);
    memcpy(uuid_tmp + 4, &ts, 4);
    snprintf(str_result, sizeof(str_result), "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
            uuid_tmp[0], uuid_tmp[1], uuid_tmp[2], uuid_tmp[3],
            uuid_tmp[4], uuid_tmp[5], uuid_tmp[6], uuid_tmp[7],
            uuid_tmp[8], uuid_tmp[9], uuid_tmp[10], uuid_tmp[11]);
    return std::string(str_result);
}

void test_insert_speed()
{
    SttMongoDB mongodb;
    mongodb.Connect("192.168.7.202", 27017);
    //string doc = "{'title': 'this is title', 'body': 'this is body', 'ts' :";

    for (int i = 0; i < 1000000; ++i)
    {
        time_t now_ts = time(NULL);
        std::vector<std::string> vec;
        vec.push_back("{ \"_id\" : \"" + uuid(now_ts) + "\", \"body\" : \"夏天就是要一边吃西瓜，一边参加斗鱼联合京东生鲜举办的#618龙虾免费吃#“斗鱼玩转666”直播挑战赛！8日21：00-24：00 ，梦笙Evon 房间号463794、九艺然然 房间号459279，快来围观吧！\", \"dst_grp_id\" : 0, \"dst_id\" : " + boost::lexical_cast<string>(random() % 1000000) + ", \"imp\" : 0, \"mt\" : 0, \"src_id\" : 0, \"status\" : 0, \"sub\" : \"斗鱼玩转666 京东生鲜龙虾免费吃\", \"ts\" : 1465887256, \"type\" : 0 }");
        vec.push_back("{ \"_id\" : \"" + uuid(now_ts) + "\", \"body\" : \"夏天就是要一边吃西瓜，一边参加斗鱼联合京东生鲜举办的#618龙虾免费吃#“斗鱼玩转666”直播挑战赛！8日21：00-24：00 ，梦笙Evon 房间号463794、九艺然然 房间号459279，快来围观吧！\", \"dst_grp_id\" : 0, \"dst_id\" : " + boost::lexical_cast<string>(random() % 1000000) + ", \"imp\" : 0, \"mt\" : 0, \"src_id\" : 0, \"status\" : 0, \"sub\" : \"斗鱼玩转666 京东生鲜龙虾免费吃\", \"ts\" : 1465887256, \"type\" : 0 }");
        vec.push_back("{ \"_id\" : \"" + uuid(now_ts) + "\", \"body\" : \"夏天就是要一边吃西瓜，一边参加斗鱼联合京东生鲜举办的#618龙虾免费吃#“斗鱼玩转666”直播挑战赛！8日21：00-24：00 ，梦笙Evon 房间号463794、九艺然然 房间号459279，快来围观吧！\", \"dst_grp_id\" : 0, \"dst_id\" : " + boost::lexical_cast<string>(random() % 1000000) + ", \"imp\" : 0, \"mt\" : 0, \"src_id\" : 0, \"status\" : 0, \"sub\" : \"斗鱼玩转666 京东生鲜龙虾免费吃\", \"ts\" : 1465887256, \"type\" : 0 }");
        vec.push_back("{ \"_id\" : \"" + uuid(now_ts) + "\", \"body\" : \"夏天就是要一边吃西瓜，一边参加斗鱼联合京东生鲜举办的#618龙虾免费吃#“斗鱼玩转666”直播挑战赛！8日21：00-24：00 ，梦笙Evon 房间号463794、九艺然然 房间号459279，快来围观吧！\", \"dst_grp_id\" : 0, \"dst_id\" : " + boost::lexical_cast<string>(random() % 1000000) + ", \"imp\" : 0, \"mt\" : 0, \"src_id\" : 0, \"status\" : 0, \"sub\" : \"斗鱼玩转666 京东生鲜龙虾免费吃\", \"ts\" : 1465887256, \"type\" : 0 }");
        vec.push_back("{ \"_id\" : \"" + uuid(now_ts) + "\", \"body\" : \"夏天就是要一边吃西瓜，一边参加斗鱼联合京东生鲜举办的#618龙虾免费吃#“斗鱼玩转666”直播挑战赛！8日21：00-24：00 ，梦笙Evon 房间号463794、九艺然然 房间号459279，快来围观吧！\", \"dst_grp_id\" : 0, \"dst_id\" : " + boost::lexical_cast<string>(random() % 1000000) + ", \"imp\" : 0, \"mt\" : 0, \"src_id\" : 0, \"status\" : 0, \"sub\" : \"斗鱼玩转666 京东生鲜龙虾免费吃\", \"ts\" : 1465887256, \"type\" : 0 }");
        vec.push_back("{ \"_id\" : \"" + uuid(now_ts) + "\", \"body\" : \"夏天就是要一边吃西瓜，一边参加斗鱼联合京东生鲜举办的#618龙虾免费吃#“斗鱼玩转666”直播挑战赛！8日21：00-24：00 ，梦笙Evon 房间号463794、九艺然然 房间号459279，快来围观吧！\", \"dst_grp_id\" : 0, \"dst_id\" : " + boost::lexical_cast<string>(random() % 1000000) + ", \"imp\" : 0, \"mt\" : 0, \"src_id\" : 0, \"status\" : 0, \"sub\" : \"斗鱼玩转666 京东生鲜龙虾免费吃\", \"ts\" : 1465887256, \"type\" : 0 }");
        vec.push_back("{ \"_id\" : \"" + uuid(now_ts) + "\", \"body\" : \"夏天就是要一边吃西瓜，一边参加斗鱼联合京东生鲜举办的#618龙虾免费吃#“斗鱼玩转666”直播挑战赛！8日21：00-24：00 ，梦笙Evon 房间号463794、九艺然然 房间号459279，快来围观吧！\", \"dst_grp_id\" : 0, \"dst_id\" : " + boost::lexical_cast<string>(random() % 1000000) + ", \"imp\" : 0, \"mt\" : 0, \"src_id\" : 0, \"status\" : 0, \"sub\" : \"斗鱼玩转666 京东生鲜龙虾免费吃\", \"ts\" : 1465887256, \"type\" : 0 }");
        vec.push_back("{ \"_id\" : \"" + uuid(now_ts) + "\", \"body\" : \"夏天就是要一边吃西瓜，一边参加斗鱼联合京东生鲜举办的#618龙虾免费吃#“斗鱼玩转666”直播挑战赛！8日21：00-24：00 ，梦笙Evon 房间号463794、九艺然然 房间号459279，快来围观吧！\", \"dst_grp_id\" : 0, \"dst_id\" : " + boost::lexical_cast<string>(random() % 1000000) + ", \"imp\" : 0, \"mt\" : 0, \"src_id\" : 0, \"status\" : 0, \"sub\" : \"斗鱼玩转666 京东生鲜龙虾免费吃\", \"ts\" : 1465887256, \"type\" : 0 }");
        vec.push_back("{ \"_id\" : \"" + uuid(now_ts) + "\", \"body\" : \"夏天就是要一边吃西瓜，一边参加斗鱼联合京东生鲜举办的#618龙虾免费吃#“斗鱼玩转666”直播挑战赛！8日21：00-24：00 ，梦笙Evon 房间号463794、九艺然然 房间号459279，快来围观吧！\", \"dst_grp_id\" : 0, \"dst_id\" : " + boost::lexical_cast<string>(random() % 1000000) + ", \"imp\" : 0, \"mt\" : 0, \"src_id\" : 0, \"status\" : 0, \"sub\" : \"斗鱼玩转666 京东生鲜龙虾免费吃\", \"ts\" : 1465887256, \"type\" : 0 }");
        vec.push_back("{ \"_id\" : \"" + uuid(now_ts) + "\", \"body\" : \"夏天就是要一边吃西瓜，一边参加斗鱼联合京东生鲜举办的#618龙虾免费吃#“斗鱼玩转666”直播挑战赛！8日21：00-24：00 ，梦笙Evon 房间号463794、九艺然然 房间号459279，快来围观吧！\", \"dst_grp_id\" : 0, \"dst_id\" : " + boost::lexical_cast<string>(random() % 1000000) + ", \"imp\" : 0, \"mt\" : 0, \"src_id\" : 0, \"status\" : 0, \"sub\" : \"斗鱼玩转666 京东生鲜龙虾免费吃\", \"ts\" : 1465887256, \"type\" : 0 }");
        vec.push_back("{ \"_id\" : \"" + uuid(now_ts) + "\", \"body\" : \"夏天就是要一边吃西瓜，一边参加斗鱼联合京东生鲜举办的#618龙虾免费吃#“斗鱼玩转666”直播挑战赛！8日21：00-24：00 ，梦笙Evon 房间号463794、九艺然然 房间号459279，快来围观吧！\", \"dst_grp_id\" : 0, \"dst_id\" : " + boost::lexical_cast<string>(random() % 1000000) + ", \"imp\" : 0, \"mt\" : 0, \"src_id\" : 0, \"status\" : 0, \"sub\" : \"斗鱼玩转666 京东生鲜龙虾免费吃\", \"ts\" : 1465887256, \"type\" : 0 }");

        mongodb.insertDocs("innermail", "summary", vec);
    }
}

void test_query_fully()
{
    SttMongoDB mongodb;
    mongodb.Connect("192.168.7.202", 27017);
    //mongodb.Connect("192.168.1.62", 27027);
    //string doc = "{'title': 'this is title', 'body': 'this is body', 'ts' :";

    string ret = mongodb.QueryDoc("innermail", "summary", "{\"dst_id\": 21290, \"status\":{$ne : 2}}");
    //cout << ret << endl;
}

void test_query_field_to_return()
{
    SttMongoDB mongodb;
    mongodb.Connect("192.168.5.30", 27017);

    std::string ret_str;
    bool ret = mongodb.queryDoc(ret_str, "innermail", "summary", "{\"src_id\": 16044808}", NULL, 0, 0, "{\"body\": 1, \"_id\": 0}");
    cout << ret << ", " << ret_str << endl;
}

void test_query_field_to_return2()
{
    SttMongoDB mongodb;
    mongodb.Connect("192.168.5.13", 27017);

    std::string ret_str;
    bool ret = mongodb.queryDoc(ret_str, "user_batch_mail", "summary", "{\"uid\": 3}", NULL, 0, 0, "{\"all_count\": 0}");
    cout << ret << ", " << ret_str << endl;
}

void insert_some_data(const char *ip,  uint16_t port, uint32_t count)
{
    SttMongoDB mongodb;
    mongodb.Connect(ip, port);

    for(uint32_t i = 0; i < count; ++i)
    {
        char json_doc[1024] = {0};
        snprintf(json_doc, sizeof(json_doc), "{\"uid\" : %d, \"mid\": \"%d\"}", i, rand() % 10000000 + 1);

        std::string err_info;
        bool ret = mongodb.InsertDoc("mytest", "demo", json_doc, err_info);

        if(false == ret)
        {
            TL_FAST_LOG("err.log", tlstNoSplit, "%d failed %s", i, err_info.c_str());
        }
    }
}

bool mail_array_to_json(std::vector<int32_t> arr, int32_t uid, std::string & json_doc)//json to log
{
    Json::Value v_list(Json::arrayValue);

    BOOST_FOREACH(int32_t mid, arr)
    {
        v_list.append(mid);
    }

    Json::Value v_obj;
    v_obj["uid"] = uid;
    v_obj["mid"] = v_list;

    Json::FastWriter writer;

    json_doc = writer.write(v_obj);

    return true;
}

bool mail_json_to_array(const char *json_doc, int32_t &uid, vector<int32_t> &arr)
{
    Json::Reader reader;
    Json::Value root;
    reader.parse(json_doc, root, false);

    if (root.isArray() && root.size() == 1)
    {
        for (int i = 0; i < root.size(); ++i)
        {
            uid = root[i]["uid"].asInt();
            if (root[i]["mid"].isNull() || !root[i]["mid"].isArray())
            {
                return false;
            }

            for (int j = 0; j < root[i]["mid"].size(); j++)
            {
                int32_t mid = root[i]["mid"][j].asInt();
                arr.push_back(mid);
            }
        }

        return true;

    }
    else
    {
        return false;
    }
}

void insert_some_data2(const char *ip,  uint16_t port, uint32_t count, int32_t index)
{
    SttMongoDB mongodb;
    mongodb.Connect(ip, port);

    for (int j = 0; j < 1000; ++j)
    {
        for(uint32_t i = 0; i < count; ++i)
        {
            char json_doc[1024] = {0};
            snprintf(json_doc, sizeof(json_doc), "{$push: {\"mid\": %d, \"status\": %d}}", rand() % 10000000 + 1, rand() % 3);

            char json_cond[1024] = {0};
            snprintf(json_cond, sizeof(json_cond), "{\"uid\" : %d}", i + index * count);

            std::string err_info;
            bool ret = mongodb.UpdateDoc("user_batch_mail", "summary", json_cond, json_doc, err_info, true);

            if(false == ret)
            {
                TL_FAST_LOG("err.log", tlstNoSplit, "%d failed %s", i + index * count, err_info.c_str());
            }
        }
    }
}

void test_read_unread_mails()
{
    SttMongoDB mongodb;
    mongodb.Connect("10.1.104.13", 27082);

    std::string ret_str;
    std::string err_info;
    bool ret = mongodb.QueryDoc(ret_str, "user_batch_mail", "summary", "{\"uid\": 21290}", err_info);
    //bool ret = mongodb.QueryDoc(ret_str, "user_batch_mail", "summary", "{\"uid\": 21290}", err_info);

    if (ret)
    {
        std::cout << ret_str << std::endl;
    }
    else
    {
        std::cout << err_info << std::endl;
    }
}

void test_create_index()
{
    SttMongoDB mongodb;
    mongodb.Connect("10.119.26.32", 27017);

    std::string ret_str;
    std::string err_info;
    bool ret = mongodb.CreateIndex("test", "demo", "{name: 1}", err_info);
    //bool ret = mongodb.QueryDoc(ret_str, "user_batch_mail", "summary", "{\"uid\": 21290}", err_info);

    if (ret)
    {
        std::cout << ret_str << std::endl;
    }
    else
    {
        std::cout << err_info << std::endl;
    }
}

int main(int argc, char **argv)
{
    /*
    SttMongoDB *mongodb = new SttMongoDB;
    mongodb->Connect("192.168.7.202", 27017);
    string doc = "{'title': 'this is title', 'body': 'this is body', 'ts' :";
    char buf[16] = {0};
    snprintf(buf, sizeof(buf), "%lu", time(NULL));
    doc += buf;
    doc += "}";
    fprintf(stdout, "%s\n", doc.c_str());
    mongodb->InsertDoc("user_mail_db", "user_mail_collection", doc.c_str());
    sleep(10);
    */

    //test_query_fully();

#if 0

    boost::thread_group thread_gp;
    for (int i = 0; i < 128; ++i)
    {
        thread_gp.add_thread(new boost::thread(boost::bind(test_insert_speed)));
    }

    thread_gp.join_all();

    test_query_field_to_return();

    insert_some_data(100000);

    boost::thread_group thread_gp;

    for (int i = 0; i < 1000; ++i)
    {
        thread_gp.add_thread(new boost::thread(boost::bind(insert_some_data2, "10.1.141.41", 27017, 100000, i)));
    }

    thread_gp.join_all();



    //test_query_field_to_return2();

    test_read_unread_mails();

#endif

    test_create_index();

    return 0;
}

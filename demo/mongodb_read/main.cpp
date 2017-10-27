#include "stdafx.h"
#include <SttMongoDB/SttMongoDB.h>

void query_some_data(const char *ip,  uint16_t port, uint32_t count)
{
    SttMongoDB mongodb;
    mongodb.Connect(ip, port);

    for(uint32_t i = 0; i < count; ++i)
    {
        char json_doc[1024] = {0};
        snprintf(json_doc, sizeof(json_doc), "{\"numb\": %d}", rand() % 10000000 + 1);

        std::string ret_str;
        std::string err_info;
        bool ret = mongodb.QueryDoc(ret_str, "mytest", "demo", json_doc, err_info);

        if(false == ret)
        {
            TL_FAST_LOG("err.log", tlstNoSplit, "%d failed %s", i, err_info.c_str());
        }
    }
}

int main(int argc, char **argv)
{
    boost::thread_group thread_gp;
    for (int i = 0; i < 256; ++i)
    {
        thread_gp.add_thread(new boost::thread(boost::bind(query_some_data, "10.1.141.41", 27017, 10000)));
    }

    thread_gp.join_all();

    return 0;
}

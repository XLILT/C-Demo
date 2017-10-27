#include "stdafx.h"
#include <RedisDB/RedisDB.h>
#include <RedisDB/SttRedisContainers.h>
#include <MsgClientLib/MsgClient.h>

using namespace RedisContainer;

bool test_redis(int count)
{
    bool bRet = false;
    SttRedisDB * db = new SttRedisDB();
    const char *s_ip = "127.0.0.1";
    uint16_t n_port = 6379;
    const char *s_prefix = "";
    if (db->Connect(s_ip, n_port, s_prefix) == false)
    {
        printf("SttRedisDB::Connect(%s, %d) failed\r\n", s_ip, n_port);
        bRet = false;
    }
    else
    {
        uint64_t start_tick = SttGetTickCount();
        for(int i = 0; i < count; ++i)
        {
            Hash redis_hash;
            redis_hash.attachRedisDB(db);

            char *key_name = const_cast<char *>("test_key_0330");
            string str_count = convertToString(i);
            redis_hash.set(key_name, const_cast<char *>(str_count.c_str()), const_cast<char *>(str_count.c_str()));
            db->expire(key_name, 86400);
        }
        
        uint64_t stop_tick = SttGetTickCount();
        printf("redis set %d times cost %lums\n\n", count, stop_tick - start_tick);
    }

    delete db;
    return bRet;
}

void batch_test_redis(int task_count, int thread_count)
{
    int task_count_per_thread = 0;
    if(0 != thread_count)
    {
        task_count_per_thread = task_count / thread_count;
    }

    boost::thread_group th_group;
    
    uint64_t start_tick = SttGetTickCount();
    for(int i = 0; i < thread_count; ++i)
    {
        th_group.add_thread(new boost::thread(boost::bind(&test_redis, task_count_per_thread)));
    }
    
    th_group.join_all();
    uint64_t stop_tick = SttGetTickCount();
    printf("batch redis set %d times with %d threads const %lums\n\n", task_count, thread_count, stop_tick - start_tick);
}

void test_stt_rpc(int count)
{
    SttAsyncQueue AsyncQueue;
    SttTimerTask timer(AsyncQueue);
    MsgClient msg_client(&timer); 

    msg_client.SetServer("127.0.0.1", 11001);
    msg_client.Login(0, "", "");

    SttSleep(5000);

    uint64_t start_tick = SttGetTickCount();
    for(int i = 0; i < count; ++i)
    {
        SttString stt_str;
        msg_client.call_remote_function(60001, 5000, &stt_str, "rpc_msg", "");
    }

    uint64_t stop_tick = SttGetTickCount();
    printf("rpc  %d times cost %lums\n\n", count, stop_tick - start_tick);

}

int main(int argc, char **argv)
{
    int task_count = argc > 1 ? atoi(argv[1]) : 1;
    int thread_count = argc > 2 ? atoi(argv[2]) : 2;

    test_redis(task_count);

    test_stt_rpc(task_count);

    //batch_test_redis(task_count, thread_count);

    return 0;
}


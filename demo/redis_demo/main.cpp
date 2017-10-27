#include "stdafx.h"
#include <RedisDB/RedisDB.h>
#include <RedisDB/SttRedisContainers.h>

using namespace Stt::DB;

bool hval()
{
    std::string err_info;
    SttRedisDB redis;
    if ( !redis.Connect(err_info, "10.1.141.41", 6379, "user_mail:") )
    {
        return false;
    }

    bool ret = true;
    do
    {
        RedisContainer::Hash redis_hash;
        if( !redis_hash.attachRedisDB(&redis) )
        {
            ret = false;
            break;
        }

        uint64_t start_unread = SttGetUsTickCount();
        // get unread
        RedisValueArray unread_pair_arr;
        if (redis_hash.getAllValues("21290_unread", &unread_pair_arr) < 0)
        {
            ret = false;
            break;
        }
        else
        {
            if (unread_pair_arr.empty())
            {
                // not exist
                ret = false;
                break;
            }
        }

        std::cout << "get unread cost " << SttGetUsTickCount() - start_unread << " us" << std::endl;

        std::cout << unread_pair_arr.size() << std::endl;

        start_unread = SttGetUsTickCount();

        RedisValueArray read_pair_arr;
        if (redis_hash.getAllValues("21290_read", &read_pair_arr) < 0)
        {
            ret = false;
            break;
        }
        else
        {
            if (read_pair_arr.empty())
            {
                // not exist
                ret = false;
                break;
            }
        }

        std::cout << "get read cost " << SttGetUsTickCount() - start_unread << " us" << std::endl;

        std::cout << read_pair_arr.size() << std::endl;

    } while (0);

    redis.Close();
    return ret;
}

int main(int argc, char **argv)
{
    hval();

    return 0;
}

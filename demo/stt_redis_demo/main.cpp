#include "stdafx.h"
#include <RedisDB/RedisDB.h>
#include <RedisDB/SttRedisContainers.h>
#include <sstream>

template<typename T>
std::string to_string(T val)
{
    std::stringstream ss;
    ss << val;

    return ss.str();
}

void test_mset()
{
    SttRedisDB db;
    if ( !db.Connect("192.168.31.32", 6379, "test:"))
    {
        cout << "connect error" << endl;
        return;
    }

    for (int j = 0; j < 100; ++j)
    {
        RedisPairArray redis_arr;
        for(int i = 0; i < 600; ++i)
        {
            std::string str;
            str = i;
            redis_arr.push_back( std::make_pair("field" + to_string(i), "value") );
        }

        RedisContainer::Hash redis_hash;
        redis_hash.attachRedisDB( &db );
        if ( !redis_hash.mset((std::string("key") + to_string(j)).c_str(), &redis_arr))
        {
            cout << "mset " << redis_arr.size() << " error" << endl;
        }
        else
        {
            //cout << "mset " << redis_arr.size() << " ok" << endl;
        }
    }
}

int main(int argc, char **argv)
{
    boost::thread_group tg;
    for (int i = 0; i < 1000; ++i)
    {
        tg.add_thread(new boost::thread(boost::bind(test_mset)));
    }

    tg.join_all();
    //test_mset();

    return 0;
}

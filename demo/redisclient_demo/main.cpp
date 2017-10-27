#include "stdafx.h"

#include <RedisDB/RedisDB.h>
#include <RedisDB/SttRedisContainers.h>

using namespace RedisContainer;

static const char * TEST_SERVER_IP = "127.0.0.1";
static uint16_t  TEST_SERVER_PORT = 6379;

void TestRedisDB()
{
    printf("%s:%d\n", TEST_SERVER_IP, TEST_SERVER_PORT);
    SttRedisDB * db = new SttRedisDB();
    db->Connect(TEST_SERVER_IP, TEST_SERVER_PORT, "gamevod:");
    {
        SttRedisResult r;
        db->Del("aa");
    }

    {
        db->Set("aa", "100");
        char aa[256] = "";
        SttRedisResult r;
        if (&r == db->Get(&r, "aa") && r.GetType() == REDIS_REPLY_STRING)
        {
            strcpy(aa, r.GetStr());
        }
        if (strcmp(aa, "100"))
        {
            printf("SET aa 100:failed, expect : aa = 100, line:%d\r\n", __LINE__);
        }
    }

    {
        int64_t aa = 0;
        aa = db->Inc("aa");
        if (aa != 101)
        {
            printf("incr aa:failed, expect : aa = 101, line:%d\r\n", __LINE__);
        }
    }

    {
        int64_t aa = 0;
        aa = db->Dec("aa");
        if (aa != 100)
        {
            printf("decr aa:failed, expect : aa = 100, line:%d\r\n", __LINE__);
        }
    }

    {
        db->Set("aa", "HelloKitty dfgsdfg hfdhgfd");
        char v[256] = {0};
        SttRedisResult r;
        if (&r == db->Get(&r, "aa"))
        {
            if (r.GetType() == REDIS_REPLY_STRING)
            {
                strncpy(v, r.GetStr(), sizeof(v));
            }
        }
        if (strcmp(v, "HelloKitty dfgsdfg hfdhgfd"))
        {
            printf("set aa HelloKitty dfgsdfg hfdhgfd:failed, r:%s\r\n", v);
        }
    }
    db->Del("aa");

    db->Close();

    printf("TestRedisDB over\n");
    delete db;
}

void TestRedisList()
{
    SttRedisDB* db = new SttRedisDB();
    db->Connect(TEST_SERVER_IP, TEST_SERVER_PORT, "gamevod:");
    db->Del("name");

    List list;
    list.attachRedisDB(db);
    if (list.length("name") != 0)
    {
        printf("list.length(name) failed:length == 0\r\n");
    }
    list.push_back("name", "chen");
    if (list.length("name") != 1)
    {
        printf("list.length(name) failed, expect : length == 1\r\n");
    }
    list.push_back("name", "zhang");
    if (list.length("name") != 2)
    {
        printf("list.length(name) failed, expect : length == 2\r\n");
    }
    list.pop_back("name");
    if (list.length("name") != 1)
    {
        printf("list.length(name) failed, expect : length == 1\r\n");
    }
    list.push_back("name", "zhang");
    {
        SttRedisResult r;
        list.pop_back("name", &r);
        char v[256] = {0};
        if (r.GetType() == REDIS_REPLY_STRING)
        {
            strcpy(v, r.GetStr());
        }
        if (strcmp(v, "zhang"))
        {
            printf("list.pop_back(name) failed, expect : v == zhang\r\n");
        }
    }
    list.push_back("name", "zhang");
    list.push_back("name", "yang");
    {
        RedisValueArray names;
        list.range("name",0,5,&names);
        if (names.size() != 3)
        {
            printf("list.range(name) failed, expect : names.size() == 3\r\nnames:");
            for (int i = 0; i < (int)names.size(); i++)
            {
                printf(" %s", names[i].c_str());
            }
            printf("\r\n");
        }
    }
    {
        char v[256] = {0};
        SttRedisResult r;
        if (&r == list.get_item("name", 0, &r))
        {
            strcpy(v, r.GetStr());
        }
        if (strcmp(v, "chen"))
        {
            printf("list.get_item(name, 0) failed, expect : r == chen\r\n");
        }
    }
    db->Del("name");
    db->Close();

    printf("TestRedisList over\n");
    delete db;
}
void TestRedisSet()
{
    SttRedisDB* db = new SttRedisDB();
    db->Connect(TEST_SERVER_IP, TEST_SERVER_PORT, "gamevod:");
    db->Del("company");
    db->Del("company2");

    Set set;
    set.attachRedisDB(db);

    if (set.length("company") != 0)
    {
        printf("set.length(company) failed, expect : r = 0, line:%d\r\n", __LINE__);
    }

    set.add("company", "jd");
    if (set.length("company") != 1)
    {
        printf("set.length(company) failed, expect : r = 1, line:%d\r\n", __LINE__);
    }
    {
        char v[256] = "";
        SttRedisResult r;
        if (set.pop("company", &r) && r.GetType() == REDIS_REPLY_STRING)
        {
            strcpy(v, r.GetStr());
        }
        if (strcmp(v, "jd"))
        {
            printf("set.pop(company) failed, expect : r == jd, line:%d\r\n", __LINE__);
        }
    }

    set.add("company", "jd");
    set.add("company", "taobao");
    set.add("company", "jieniu");

    set.add("company2", "jd");
    set.add("company2", "taobao2");
    set.add("company2", "jieniu2");

    {
        RedisValueArray values;
        set.members("company",&values);
        if (values.size() != 3)
        {
            printf("set.members(company) failed, expect : values.size() = 3, line:%d\r\n", __LINE__);
        }
    }
    {
        RedisValueArray keys,values;
        keys.push_back("company");
        keys.push_back("company2");
        set.unions(&keys,&values);
        if (values.size() != 5)
        {
            printf("set.unions(company, company2) failed, expect : values.size() = 3, line:%d\r\n", __LINE__);
        }
    }

    {
        RedisValueArray keys,values;
        keys.push_back("company");
        keys.push_back("company2");
        set.diffs(&keys,&values);
        if (values.size() != 2)
        {
            printf("set.diffs(company, company2) failed, expect : values.size() = 3, line:%d\r\n", __LINE__);
        }
    }

    {
        RedisValueArray keys,values;
        keys.push_back("company");
        keys.push_back("company2");
        set.intersect(&keys,&values);
        if (values.size() != 1)
        {
            printf("set.intersect(company, company2) failed, expect : values.size() = 0, line:%d\r\n", __LINE__);
        }
    }

    db->Del("company");
    db->Del("company2");
    db->Close();

    printf("TestRedisSet over\n");
    delete db;
}
void TestRedisHash()
{
    SttRedisDB* db = new SttRedisDB();
    db->Connect(TEST_SERVER_IP, TEST_SERVER_PORT, "gamevod:");
    db->Del("name-age");

    Hash hash;
    hash.attachRedisDB(db);
    {
        RedisPairArray pairs;
        hash.getAll("name-age", &pairs);
        if (pairs.size() != 0)
        {
            printf("hash.getAll(name-age) failed, expect : pairs.size() = 0, line:%d\r\n", __LINE__);
        }
    }
    hash.set("name-age", "chen", "27");
    hash.set("name-age", "zhang", "29");
    hash.set("name-age", "yang", "28");
    {
        if (hash.length("name-age") != 3)
        {
            printf("hash.length(name-age) failed, expect : length = 3, line:%d\r\n", __LINE__);
        }
    }
    {
        char age[256] = "";
        SttRedisResult r;
        if(hash.get("name-age", "chen", &r) == &r)
        {
            strcpy(age, r.GetStr());
        }
        if (strcmp(age, "27"))
        {
            printf("hash.get(name-age, chen) failed, expect : age = 27, line:%d\r\n", __LINE__);
        }
    }
    hash.set("name-age", "chen", "26");
    {
        if (hash.length("name-age") != 3)
        {
            printf("hash.length(name-age) failed, expect : length = 3, line:%d\r\n", __LINE__);
        }
    }
    {
        char age[256] = "";
        SttRedisResult r;
        if(hash.get("name-age", "chen", &r) == &r)
        {
            strcpy(age, r.GetStr());
        }
        if (strcmp(age, "26"))
        {
            printf("hash.get(name-age, chen) failed, expect : age = 26, line:%d\r\n", __LINE__);
        }
    }
    {
        RedisPairArray pairs;
        hash.getAll("name-age",&pairs);
        if (pairs.size() != 3)
        {
            printf("hash.getAll(name-age, chen) failed, expect : size = 3, line:%d\r\n", __LINE__);
        }
    }
    {
        RedisValueArray keys;
        hash.getAllKeys("name-age",&keys);
        if (keys.size() != 3)
        {
            printf("hash.getAllKeys(name-age, chen) failed, expect : size = 3, line:%d\r\n", __LINE__);
        }
    }
    {
        RedisValueArray keys;
        hash.getAllValues("name-age",&keys);
        if (keys.size() != 3)
        {
            printf("hash.getAllValues(name-age, chen) failed, expect : size = 3, line:%d\r\n", __LINE__);
        }
    }
    {
        RedisPairArray pairs;
        pairs.push_back(std::make_pair("yi", "25"));
        pairs.push_back(std::make_pair("cao", "27"));
        hash.mset("name-age",&pairs);
    }
    {
        RedisValueArray field;
        RedisValueArray value;
        field.push_back("yi");
        field.push_back("cao");

        hash.mget("name-age", &field, &value);
        if (value.size() != 2)
        {
            printf("hash.getAll(name-age, chen) failed, expect : size = 5, line:%d\r\n", __LINE__);
        }
    }
    {
        RedisPairArray pairs;
        hash.getAll("name-age",&pairs);
        if (pairs.size() != 5)
        {
            printf("hash.getAll(name-age, chen) failed, expect : size = 5, line:%d\r\n", __LINE__);
        }
    }
    {
        hash.del("name-age", "yi");
        RedisPairArray pairs;
        hash.getAll("name-age",&pairs);
        if (pairs.size() != 4)
        {
            printf("hash.getAll(name-age, chen) failed, expect : size = 4, line:%d\r\n", __LINE__);
        }
    }
    {
        hash.del("name-age", "yi2");
        RedisPairArray pairs;
        hash.getAll("name-age",&pairs);
        if (pairs.size() != 4)
        {
            printf("hash.getAll(name-age, chen) failed, expect : size = 4, line:%d\r\n", __LINE__);
        }
    }
    db->Del("name-age");
    db->Close();

    printf("TestRedisHash over\n");
    delete db;
}

int main(int argc, char **argv)
{
    if (argc >= 3)
    {
        TEST_SERVER_IP = argv[1];
        TEST_SERVER_PORT = atoi(argv[2]);
        /* code */
    }

    TestRedisDB();

    TestRedisList();

    TestRedisSet();

    TestRedisHash();

    return 0;
}

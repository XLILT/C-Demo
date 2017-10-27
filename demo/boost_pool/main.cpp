#include "stdafx.h"

struct PoolTag1 {};

typedef boost::singleton_pool<PoolTag1, sizeof(int32_t)> MyPool;

void singleton_pool_demo()
{
    std::vector<int32_t *> p_list;

    int ALLOC_CNT = 100000;
    for (int i = 0; i < ALLOC_CNT; ++i)
    {
        int32_t * const t = static_cast<int32_t *>(MyPool::malloc());
        *t = 0;

        p_list.push_back(t);
    }

    std::cout << "alloc over" << std::endl;
    getchar();

    for (int i = 0; i < ALLOC_CNT; ++i)
    {
        //MyPool::free(p_list[i], sizeof(int32_t));
        //MyPool::free(p_list[i]);
        MyPool::ordered_free(p_list[i]);
    }

    for (int i = ALLOC_CNT - 1; i >= 0; --i)
    {
        //MyPool::free(p_list[i], sizeof(int32_t));
        //MyPool::free(p_list[i]);
        //MyPool::ordered_free(p_list[i]);
    }

    {
        std::vector<int32_t *> tmp_list;
        p_list.swap(tmp_list);
    }

    std::cout << "free over" << std::endl;

    getchar();

#if 0
    int cnt = 1;
    bool ret = MyPool::release_memory();
    while(!ret)
    {
        ++cnt;
        ret = MyPool::release_memory();
    }

    std::cout << "release over after " << cnt << " times" << std::endl;
#endif

    std::cout << MyPool::release_memory() << std::endl;
    std::cout << "release over" << std::endl;

    getchar();
    std::cout << MyPool::purge_memory() << std::endl;
    std::cout << "purge over" << std::endl;

    getchar();
}

int main(int argc, char **argv)
{
    singleton_pool_demo();

    return 0;
}

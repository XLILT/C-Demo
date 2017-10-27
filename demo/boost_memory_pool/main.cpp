#include <boost/pool/singleton_pool.hpp>
#include <stdio.h>
#include <CommonBase/Utility.h>

struct MyPoolTag {};

typedef boost::singleton_pool<MyPoolTag, sizeof(int)> MyIntPool;
boost::pool<> my_pool(sizeof(int));

//#define MY_MALLOC(pool) pool::malloc()
//#define MY_MALLOC(pool) new int
#define MY_MALLOC(pool) my_pool.malloc()
//#define MY_MALLOC(pool) my_pool.ordered_malloc()

//#define MY_FREE(pool, p) pool::free(p)
//#define MY_FREE(pool, p) delete p
#define MY_FREE(pool, p) my_pool.free(p)
//#define MY_FREE(pool, p) my_pool.ordered_free(p)


int main()
{
    const int CNT = 2;

    uint64_t start = SttGetTickCount();
    int *x[CNT];
    for (int i = 0; i < CNT; ++i)
    {
        /* code */
        //x[i] = reinterpret_cast<int *>(MyIntPool::malloc());
        //x[i] = reinterpret_cast<int *>(MyIntPool::ordered_malloc());
        //x[i] = new int;
        x[i] = reinterpret_cast<int *>(MY_MALLOC(MyIntPool));
        //printf("%d --- %lu, %lu\n", i, my_pool.get_max_size(), my_pool.get_next_size());
    }

    printf("malloc over const %lu\n", SttGetTickCount() - start);
    getchar();

    start = SttGetTickCount();
    for (int i = 0 ; i < CNT; ++i)
    {
        /* code */
        //MyIntPool::free(x[i]);
        //MyIntPool::ordered_free(x[i]);
        MY_FREE(MyIntPool, x[i]);
        //delete x[i];
    }

    printf("free over const %lu\n", SttGetTickCount() - start);
    getchar();

    start = SttGetTickCount();
    //MyIntPool::release_memory();
    bool ret = my_pool.release_memory();

    printf("release over const %lu return %d\n", SttGetTickCount() - start, ret);
    getchar();

    start = SttGetTickCount();
    //MyIntPool::release_memory();
    ret = my_pool.release_memory();

    printf("release over const %lu return %d\n", SttGetTickCount() - start, ret);
    getchar();

    start = SttGetTickCount();
    //MyIntPool::release_memory();
    ret = my_pool.release_memory();

    printf("release over const %lu return %d\n", SttGetTickCount() - start, ret);
    getchar();

    start = SttGetTickCount();
    //MyIntPool::release_memory();
    ret = my_pool.release_memory();

    printf("release over const %lu return %d\n", SttGetTickCount() - start, ret);
    getchar();

    start = SttGetTickCount();
    //MyIntPool::purge_memory();
    my_pool.purge_memory();

    printf("purge over const %lu\n", SttGetTickCount() - start);
    getchar();

    return 0;
}

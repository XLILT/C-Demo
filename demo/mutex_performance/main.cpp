#include "stdafx.h"

static boost::mutex ml;

void cost_test()
{
    uint64_t start = SttGetTickCount();
    for (int i = 0; i < 1000000; ++i)
    {
        ml.lock();
        ml.unlock();
    }

    cout << pthread_self() << " lock && unlock 1000000 times cost " << SttGetTickCount() - start << "ms" << endl;
}

int main(int argc, char **argv)
{
    boost::thread_group thread_gp;
    for (int i = 0; i < 10; ++i)
    {
        thread_gp.add_thread( new boost::thread(boost::bind(cost_test)));
    }

    thread_gp.join_all();

    return 0;
}

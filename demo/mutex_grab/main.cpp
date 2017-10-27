#include "stdafx.h"

static boost::mutex g_lock;

void grab_mutex(int i)
{
    g_lock.lock();
    cout << i << " grab g_lock" << endl;
    g_lock.unlock();
}

int main(int argc, char **argv)
{
    g_lock.lock();
    boost::thread_group thread_gp;
    for (int i = 0; i < 1000; ++i)
    {
        thread_gp.add_thread(new boost::thread(boost::bind(grab_mutex, i)));
    }

    g_lock.unlock();
    thread_gp.join_all();

    return 0;
}

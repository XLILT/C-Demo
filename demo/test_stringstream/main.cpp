#include "stdafx.h"
#include <sstream>

void f(int x)
{
    for (int i = 0; i < 100000; ++i)
    {
        stringstream ss;
        int y = 1234;
        ss << y;
    }

}

int main(int argc, char **argv)
{
    boost::thread_group th_group;
    for(int i = 0; i < atoi(argv[1]); ++i)
    {
        th_group.add_thread(new boost::thread(boost::bind(&f, i)));
        //boost::thread(boost::bind(&f));
    }

    th_group.join_all();
    cout << "over" << endl;

    return 0;
}

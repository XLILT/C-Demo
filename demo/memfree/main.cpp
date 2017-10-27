#include <stdio.h>
#include <iostream>
#include <string>
#include <list>
#include <boost/pool/singleton_pool.hpp>
#include <boost/date_time/posix_time/time_formatters.hpp>

using namespace std;

struct pool_tag{};
//typedef boost::singleton_pool<pool_tag, 4096, boost::default_user_allocator_new_delete, boost::mutex, 1, 1> my_pool;
typedef boost::singleton_pool<pool_tag, 4096, boost::default_user_allocator_new_delete, boost::mutex, 32, 0> my_pool;
//typedef boost::singleton_pool<pool_tag, 4> my_pool;

int main()
{
    {
        char tmp_str[64];
        //list<int> m_list;
        //m_list.push_back(1);
        //list<int> m_list;

        while(string(tmp_str) != "exit")
        {
            int *p[1000000];

            boost::posix_time::ptime pt_start = boost::posix_time::microsec_clock::local_time();

            for (int i = 0; i < 1000000; i++)
            {
                //p[i] = (int *)my_pool::malloc();
                p[i] = new int[1024];
                //p[i] = (int *)malloc(1024 * 4);
                //usleep(10000);
                //cout << "malloc " << i << endl;
            }

            boost::posix_time::ptime on_malloc = boost::posix_time::microsec_clock::local_time();
            //getchar();
            //char ch[123];
            //cin >> ch;
            //string s1("123");

            //vector<int> m_v;
            //m_v.push_back(1);
            //{
            //    vector<int> tmp_v;
            //    m_v.swap(tmp_v);
            //}

            //static int *q = new int;
            //static int q;

            //cout << q << endl;
            //m_list.push_back(1);
            //{
            //    list<int> tmp_l;
            //    m_list.swap(tmp_l);
            //}
            //string *s1 = new string("123");
            //s1->append("123");
            //delete s1;
            //s1.append("123");

            //string s2;
            //s1.swap(s2);
            //cin >> s1;
            //sleep(10);
            //cout << "hehe" << endl;


            int x = 100000;
            for (int i = 0; i < x; i++)
            {
                //my_pool::free(p[i]);
                delete []p[i];
                //free(p[i]);
                //cout << "free  " << i << endl;
            }

            //delete q;
            //q = 1;

            for (int i = x; i < 1000000; i++)
            {
                //my_pool::free(p[i]);
                delete []p[i];
                //free(p[i]);
                //cout << "free  " << i << endl;
            }

            //my_pool::release_memory();
            //my_pool::purge_memory();

            boost::posix_time::ptime on_free = boost::posix_time::microsec_clock::local_time();

            cout << "free all: malloc cost: " << boost::posix_time::to_iso_string(on_malloc - pt_start)
                << ", free cost: " << boost::posix_time::to_iso_string(on_free - on_malloc) << endl;
            cin >> tmp_str;
        }

        //{
        //    list<int> tmp_l;
        //    m_list.swap(tmp_l);
        //}
        //m_list.resize(0);
    }

    while(1)
        cout << "out of while" << endl;
        //printf("out of while\n");

    return 0;
}


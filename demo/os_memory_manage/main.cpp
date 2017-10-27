//#include "stdafx.h"
#include <iostream>
#include <list>
#include <boost/container/detail/singleton.hpp>
#include <boost/unordered_map.hpp>
#include <string>
#include <stdio.h>

//#include <netmsg/netmsg_title.h>

using namespace std;

/*
namespace JXTitle {

class UserLevelCalculator1
{
public:
    UserLevelCalculator1()
        {
            _level_upgrade_experience_map[1] = 0;
            //_level_total_experience_map[1] = _level_total_experience_map[0] + 0;
            //_level_total_experience_map[1] = 0;
            //_level_total_experience_map[2] = 0;
            //_total_experience_level_map[_level_total_experience_map[1]] = 1;

            _level_upgrade_experience_map[2] = 10;
            //_level_total_experience_map[2] = _level_total_experience_map[1] + 10;
            //_level_total_experience_map[3] = _level_total_experience_map[1] + 10;
            //_total_experience_level_map[_level_total_experience_map[2]] = 2;

            _level_upgrade_experience_map[3] = 10;
            _level_upgrade_experience_map[4] = 10;
            _level_upgrade_experience_map[5] = 10;
            _level_upgrade_experience_map[6] = 10;
            _level_upgrade_experience_map[7] = 10;
            _level_upgrade_experience_map[8] = 10;
            _level_upgrade_experience_map[9] = 10;
        }

    ~UserLevelCalculator1() {}
    //friend struct boost::container::container_detail::singleton_default<UserLevelCalculator>;

    std::map<int64_t, int> _total_experience_level_map;
    //boost::unordered_map<int, int64_t> _level_total_experience_map;
    boost::unordered_map<int, int64_t> _level_upgrade_experience_map;
};

typedef boost::container::container_detail::singleton_default<UserLevelCalculator1> SingletonUserLevelCalculator1;

}

static void calculate_level()
{
    JXTitle::SingletonUserLevelCalculator1::instance();
}

*/

/*
void test_vector()
{
    int *p[1000000];

    for (int i = 0; i < 100000; i++)
    {
        //p[i] = (int *)my_pool::malloc();
        p[i] = new int[1024];
        //p[i] = (int *)malloc(1024 * 4);
        //usleep(10000);
        //cout << "malloc " << i << endl;

    }

    vector<int> m_v;
    m_v.push_back(1);

    cout << "malloc over" << endl;
    getchar();

    int x = 100000;
    for (int i = 0; i < x; i++)
    {
        //my_pool::free(p[i]);
        delete []p[i];
        //free(p[i]);
        //cout << "free  " << i << endl;
    }

    cout << "free over" << endl;
    getchar();
}
*/

int main(int argc, char **argv)
{
    //test_vector();

    char tmp_str[64] = {0};

    while(string(tmp_str) != "exit")
    {
        int *p[100000];

        for (int i = 0; i < 100; i++)
        {
            //p[i] = (int *)my_pool::malloc();
            p[i] = new int[1024 * 1024];
            //p[i] = (int *)malloc(1024 * 4);
            //usleep(10000);
            //cout << "malloc " << i << endl;

        }

        cout << "malloc over" << endl;
        getchar();

        //list<int> m_list;
        //m_list.push_back(1);
        int *x = new int;

        cout << "push back over" << endl;
        getchar();

        //cout << "malloc over" << endl;
        //getchar();

        for (int i = 0; i < 100; i++)
        {
            //my_pool::free(p[i]);
            delete []p[i];
            //free(p[i]);
            //cout << "free  " << i << endl;
        }

        cout << "free over" << endl;
        //getchar();

        cin >> tmp_str;
    }

    return 0;
}

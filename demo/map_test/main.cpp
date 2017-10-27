#include <iostream>
#include <map>
#include <stdio.h>
#include "stdafx.h"

using namespace std;

class A
{
public:
    static void f(int i)
    {
        cout << "aaa, " << i << endl;
    }
};

int main()
{
    //map< int, map<int, int> > id_map_map;
    //cout << id_map_map[1][1] << endl;

    //new boost::thread(boost::bind(&A::f, 1));

    //getchar();
    //cin >> NULL;
    list<int> m_list;
    map<int, int, greater<int> > m;
    for (int i = 0; i < 10; ++i)
    {
        m[i] = i;
        m_list.push_back(i);
    }

    typedef map<int, int>::value_type MapValueType;
    //BOOST_FOREACH(const MapValueType &cpair, m)
    //{
    //    cout << cpair.first << " => " << cpair.second << endl;
    //}

    map<int, int, greater<int> >::const_iterator cit = m.find(5);

    m.erase(3);
    //cout << "after erase 3 " << cit->first << endl;

    m.erase(4);
    //cout << "after erase 4 " << cit->first << endl;

    list<int>::iterator l_it = m_list.begin();
    l_it++;
    l_it++;

    m_list.splice(m_list.begin(), m_list, l_it);
    cout << *l_it << endl;

    return 0;
}

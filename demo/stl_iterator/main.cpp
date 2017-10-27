#include "stdafx.h"
#include <map>

using namespace std;

void test_set()
{
    set<int> set1;

    set1.insert(0);
    set1.insert(1);
    set1.insert(2);
    set1.insert(3);
    set1.insert(4);

    int set1_size = set1.size();
    set<int>::iterator *cit_arr = new set<int>::iterator[set1_size];

    int i = 0;
    set<int>::iterator cit = set1.begin();
    while(cit != set1.end())
    {
        //*cit +=  10;
        cit_arr[i++] = cit++;
    }

    /*
    set1.insert(5);
    set1.insert(6);

    set1.erase(6);
    set1.erase(5);
    set1.erase(4);
    set1.erase(3);
    set1.erase(2);
    */

    for (int j = 0; j < set1_size; ++j)
    {
        //*cit_arr[j] = j + 10;
        cout << *cit_arr[j] << endl;
    }

    cout << "---" << endl;

    cit = set1.begin();
    while(cit != set1.end())
    {
        cout << *cit++ << endl;
    }
}

void test_map()
{
    map<int, int> map1;

    for (int i = 0; i < 10; ++i)
    {
        map1[i] = i;
    }

    int map1_size = map1.size();
    map<int, int>::iterator *it_arr = new map<int, int>::iterator[map1_size];

    int i = 0;
    for (map<int, int>::iterator it = map1.begin(); it != map1.end(); ++it)
    {
        it_arr[i] = it;
    }

    it_arr[0]->second = 10;

    //map1.begin()->second += 10;

    for (map<int, int>::const_iterator cit = map1.begin(); cit != map1.end(); ++cit)
    {
        cout << cit->first << " => " << cit->second << endl;
    }
}

int main(int argc, char **argv)
{
    //test_set();
    test_map();

    return 0;
}

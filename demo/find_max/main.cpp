#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#define TEN 10
#define THREE 3

using namespace std;

int main()
{
    map<int, int> m;

    int len = TEN;
    while(len--)
    {
        int i = 0;
        cin >> i;

        m[i] = i;
    }

    if(m.size() < THREE)
    {
        cout  << "on more then 3 different numbers" << endl;
    }

    vector<int> v;
    for(map<int, int>::iterator it = m.begin(); it != m.end(); it++)
    {
        v.push_back(it->first);
    }

    sort(v.begin(), v.end(), greater<int>() );

    cout << "max is: " << 100 * v[0] + 10 * v[1] + v[2];
    return 0;
}


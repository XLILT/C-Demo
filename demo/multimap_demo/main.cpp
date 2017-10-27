#include "stdafx.h"
#include <string>
#include <map>

typedef const multimap<int, string>::value_type ConstPair;

void print_mm(multimap<int, string, std::greater<const int> > &mm)
{
    BOOST_FOREACH(ConstPair &pair, mm)
    {
        cout << pair.first << " => " << pair.second << endl;
    }
}

int main(int argc, char **argv)
{
    multimap<int, string, std::greater<const int> > mm;
    mm.insert(pair<int, string>(2, "2"));
    mm.insert(pair<int, string>(2, "3"));
    mm.insert(pair<int, string>(1, "1"));
    mm.insert(pair<int, string>(3, "3"));
    
    print_mm(mm);

    BOOST_FOREACH(ConstPair &pair, mm)
    {
        if(pair.second == "2")
        {
            //pair.first = 4;
        }
    }
   
    print_mm(mm);

    return 0;
}

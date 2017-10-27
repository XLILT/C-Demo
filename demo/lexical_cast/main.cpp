#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>

using namespace std;

int main()
{
    string str = "123";
    int x = 0;

    try
    {
        x = boost::lexical_cast<int, string>(str);
    }
    catch(...)
    {
        cout << "what the fuck!!!" << endl;
    }

    cout << str << ", " << x << endl;
    return 0;
}


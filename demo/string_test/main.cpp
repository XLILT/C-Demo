#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

struct Foo
{
    Foo()
    {
        // Allocate 4 ints.
        m_data = new int[4];
        // Move the pointer.
        //++m_data;
        // Null the pointer
        //m_data = 0;
    }
    ~Foo()
    {
        // Put the pointer back, then delete it.
        //--m_data;
        delete [] m_data;
    }
    int* m_data;
};

int main()
{
	//string str("hehe");
	Foo f;
	exit(0);
	//return 0;
}


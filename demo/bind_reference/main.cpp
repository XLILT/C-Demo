#include "stdafx.h"

class A
{
public:
    A() {}

    A(const A &a)
    {
        cout << "copy construct is called" << endl;
    }
};

void f(const A a) {}

int main(int argc, char **argv)
{
    A a1;
    boost::bind(&f, a1);

    return 0;
}

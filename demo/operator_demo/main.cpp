#include "stdafx.h"

struct A
{
    int x;

    A()
        : x(0)
        {}

    A(int x)
        : x(x)
        {}

    A(const A &a)
        : x(a.x)
        {}
};

int main(int argc, char **argv)
{
    A a;

    cout << a.x << endl;

    return 0;
}

#include "stdafx.h"

class A
{
    int _x;

public:
    A() : _x(0) {}
    A(int x) : _x(x) {}

    int operator++(int)
    {
        return ++_x;
    }
};

int main(int argc, char **argv)
{
    A a;

    cout << a++ << endl;

    return 0;
}

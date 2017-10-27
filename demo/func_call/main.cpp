#include "stdafx.h"

class A
{
public:
    int _x;

public:
    explicit A(int x) : _x(x) {}
};

void f(A a)
{
    printf("%d\n", a._x);
}

int main(int argc, char **argv)
{
    f(88);
    return 0;
}

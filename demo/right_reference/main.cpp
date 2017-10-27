#include "stdafx.h"

void f(const int &x)
{
    cout << &x << " : " << x << endl;
}

void g(int &&x)
{
    cout << &x << " : " << x << endl;
}

int main(int argc, char **argv)
{
    int x = 777;

    f(x);
    g(int(77));

    return 0;
}

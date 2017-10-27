#include "stdafx.h"

static const char * const HW = "hello world";

void f(int x)
{
    x += x;
}

int main(int argc, char **argv)
{
    int y = 1;
    f(y);

    return 0;
}

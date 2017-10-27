#include "stdafx.h"

void test_stack_overflow(int x)
{
    if (x <= 0)
    {
        return;
    }

    int y[1024][512];
    cout << "using" << endl;

    test_stack_overflow(x - 1);
}

int main(int argc, char **argv)
{
    test_stack_overflow(atoi(argv[1]));

    cout << "free" << endl;
    getchar();
    return 0;
}

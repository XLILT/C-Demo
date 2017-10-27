#include "stdafx.h"
#include "func.h"

extern void g();

static void static_f() { cout << "static func" << endl; }

int main(int argc, char **argv)
{
    wtf1(1);
    wtf2(2);
    g();
    static_f();

    return 0;
}

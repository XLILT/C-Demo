#include "stdafx.h"
#include "A.h"

//inline void A::abcf() { cout << "f in main" << endl; }

int main(int argc, char **argv)
{
    A *a = new A;

    a->abcf();
    a->g();
    a->h();

    delete a;

    return 0;
}

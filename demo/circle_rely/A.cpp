#include "A.h"
#include "stdafx.h"

void A::g()
{
    abcf();
}

inline void A::abcf() { cout << "f in A" << endl; }

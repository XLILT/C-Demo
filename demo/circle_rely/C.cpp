#include "A.h"
#include "stdafx.h"

void A::h() { abcf(); }

inline void A::abcf() { cout << "f in C" << endl; }

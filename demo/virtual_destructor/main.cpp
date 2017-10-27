#include "stdafx.h"

class Base
{
    public:
        ~Base() {cout << "destructor of Base" << endl;}
};

class A : public Base
{
    public:
        ~A() {cout << "destructor of A" << endl;}
};

int main(int argc, char **argv)
{
    const Base &b = A();
    return 0;
}

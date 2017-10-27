#include "stdafx.h"

class Base
{
public:
    virtual void f() const
    {
        cout << "this is from Base" << endl;
    }

};

class A : public Base
{
public:
    void f() const
    {
        cout << "this is from A" << endl;
    }
};

int main(int argc, char **argv)
{
    //const Base &a = A();
    const Base &a = Base();
    a.f();

    return 0;
}

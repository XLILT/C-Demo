#include <stdio.h>

#define add(x, y) do {  \
    printf("hello add"); }while(0)


class Base
{
public:
    int x;
    virtual void f() { x = 1; }
};

class Son1 : public Base
{
public:
    void f() { x = 2; }
};

int main(int argc, char **argv)
{
    //char s[1024];
    //printf("%d, %d", sizeof(s), sizeof(Son1));
    //Base *b = new Son1();
    //b->f();

    //int x1 = 1;
    //int *x2 = new int(2);

    //char c1 = 'c';
    //char *c2 = new char('c');
    add(1, 2);

    return 0;
}

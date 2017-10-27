#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <iostream>

using namespace std;

#if 0
void* operator new(size_t size)
{
 printf("malloc %lu\r\n", size);
 return malloc(size);
}
void operator delete(void *memblock){
 printf("free\r\n");
 return free(memblock);
}

class abc{
public:
 abc(){
  printf("abc\r\n");
  throw int();
 }
 ~abc(){
  printf("~abc\r\n");
 }
};

int main(){
 try{
  new abc;
 }catch(int& i){
  printf("%d\r\n", i);
 }
 return 0;
}

template <typename T>
class abc{
public:
 abc(){
  printf("primary\r\n");
 }
};

template<>
abc<int>::abc(){
 printf("member spec\r\n");
};

template<typename T, typename P>
class abc<T (*)(P)>{
public:
 abc(){
  printf("partial spec\r\n");
 }
};

int main()
{
 abc<void* (*)(int)> f_abc;
 abc<int> i_abc;
}

class a{
public:
 virtual ~a(){
 }
private:
 void operator delete(void *p){};
};

int main()
{
 a _1;
}

#endif

// test of new throw exception

void test_new_throw_exception(size_t size)
{
    try
    {
        int *p = new int[size];

        memset(p, 0, sizeof(int) * size);
        cout << "new memory for p over" << endl;

        getchar();

        delete p;
        p = NULL;
        cout << "delete memory of p over" << endl;
    }
    catch(std::exception &e)
    {
        cout << "new throw some exception " << e.what() << endl;
    }
}

void test_placement_new()
{
    struct A
    {
        int x;

        A()
        {
            cout << "construct A" << endl;
        }

        ~A()
        {
            cout << "destruct A" << endl;
        }

        static A * Alloc()
        {
            A *p = (A *)new char[sizeof(A)];

            //return (A *)p;
            #pragma push_macro("new")
            new(p) A;
            #pragma pop_macro("new")

            return p;
        }
    };

    //A *a = A::Alloc();

    //delete []a;
    //delete a;
}

int main(int argc, char **argv)
{
    //test_new_throw_exception(atoi(argv[1]));
    for (int i = 0; i < atoi(argv[1]); ++i)
    {
        test_placement_new();
    }

    cout << "loop over" << endl;

    getchar();
    return 0;
}

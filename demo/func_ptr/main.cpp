#include "stdafx.h"
#include <unistd.h>
#include <pthread.h>

//void f(int x) { fflush(stdout); cout << "hello world " << x << endl; fflush(stdout); }
void f(int x)
{
    fflush(stdout);
    write(1, "hello world\n", strlen("hello world\n") + 1);
    fflush(stdout);
}

typedef void (*func_ptr)();

int main(int argc, char **argv)
{
    /*
    printf("%p, %p\n", f, &f);
    func_ptr p = &f;
    (*p)();
    */
    boost::thread a(boost::bind(f, atoi(argv[1])));
    //a.join();
   // pthread_t t;
   // pthread_create(&t, NULL, f, (void *)atoi(argv[1]));
//    boost::thread b(boost::bind(f, atoi(argv[1])));
    //getchar();
    return 0;
}

//#include "func.h"
#include <dlfcn.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

uint64_t SttGetTickCount()
{
    //volatile static uint64_t lastTick = 0;
    uint64_t currentTime;

    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    currentTime = (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);

    return currentTime;
}

void f1(int *x)
{
    void *pd_handle = dlopen("libfunc.so", RTLD_LAZY);
    if(NULL == pd_handle)
    {
        printf("failed to load library!\n");
        return;
    }

    char *dl_err = dlerror();
    if(NULL != dl_err)
    {
        printf("%s\n", dl_err);
        dlclose(pd_handle);
        return;
    }

    void (*funcp)(int *) = (void (*)(int *))dlsym(pd_handle, "add");

    dl_err = dlerror();
    if(NULL != dl_err)
    {
        printf("%s\n", dl_err);
        dlclose(pd_handle);
        return;
    }

    (*funcp)(x);
    //fprintf(stdout, "%d\n", *x);
    //printf("%d\n", (*funcp)(1, 1));

    dlclose(pd_handle);
}

void f2(int *x)
{
    ++(*x);
}

int main(int argc, char **argv)
{
    static int x;
    static int y;
    uint64_t start_ts = SttGetTickCount();
    uint64_t counts = 100000;

    while(1)
    {
        f1(&x);
        //getchar();
        if (x >= counts)
        {
            break;
        }
    }

    fprintf(stdout, "f1 cost %ul\n", SttGetTickCount() - start_ts);

    start_ts = SttGetTickCount();

    while(1)
    {
        f2(&y);
        //getchar();
        if (y >= counts)
        {
            break;
        }
    }

    fprintf(stdout, "f2 cost %ul\n", SttGetTickCount() - start_ts);

    //cout << add(1, 2) << endl;
    return 0;
}

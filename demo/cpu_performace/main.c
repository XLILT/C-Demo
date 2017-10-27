#include <stdint.h>
#include <stdio.h>
#include <time.h>

static uint64_t get_ns_tick_count(clockid_t cid)
{
    struct timespec ts = {0, 0};
    clock_gettime(cid, &ts);

    return ts.tv_sec * 1000000000 + ts.tv_nsec;
}

int main(int argc, char **argv)
{
    uint64_t start_ns = get_ns_tick_count(CLOCK_REALTIME);
    uint32_t i = 0;
    for(; i < 1000000000; i++)
    {
    }

    printf("loop 1 billion times cost %luns\n", get_ns_tick_count(CLOCK_REALTIME) - start_ns);

    return 0;
}

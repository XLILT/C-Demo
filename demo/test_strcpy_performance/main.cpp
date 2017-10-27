#include <stdio.h>
#include <CommonBase/Utility.h>

void test_strncpy()
{
    char tmp[1000000];

    strncpy(tmp, "hello strncpy", sizeof(tmp));
    tmp[1000000 - 1] = '\0';
}

void test_snprintf()
{
    char tmp[1000000];

    snprintf(tmp, sizeof(tmp), "%s", "hello snprintf");
}

int main(int argc, char **argv)
{
    uint64_t start = SttGetTickCount();
    for (int i = 0; i < 10000; ++i)
    {
        test_strncpy();
    }

    printf("test_strnpcy const %lu\n", SttGetTickCount() - start);

    start = SttGetTickCount();
    for (int i = 0; i < 10000; ++i)
    {
        test_snprintf();
    }

    printf("test_snprintf const %lu\n", SttGetTickCount() - start);

    return 0;
}

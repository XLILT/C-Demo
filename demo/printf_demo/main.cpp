#include "stdafx.h"

int main(int argc, char **argv)
{
    printf("#, %#64f\n", 99.99);
    printf("0, %064d\n", 100);
    printf("-, %-64d\n", 100);
    printf(" , % 64d\n", 100);
    printf("+, %+64d\n", 100);
    printf("', %'64d\n", 100);
    printf("I, %Id\n", 100);
    printf("., %.64d\n", 100);
    return 0;
}

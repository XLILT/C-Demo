#include "stdafx.h"

int main(int argc, char **argv)
{
    int *p = new int;

    cout << *(p + 1024) << endl;

    delete p;

    int *q = NULL;
    cout << *q << endl;

    return 0;
}

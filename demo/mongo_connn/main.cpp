#include "stdafx.h"
#include <SttMongoDB/SttMongoDB.h>

void get_conn(const char *host, int port, int cnt)
{
    for (int i = 0; i < cnt; ++i)
    {
        SttMongoDB *mongo = new SttMongoDB;
        mongo->Connect(host, port);
    }
}

int main(int argc, char **argv)
{
    get_conn(argv[1], atoi(argv[2]), atoi(argv[3]));
    getchar();
    return 0;
}

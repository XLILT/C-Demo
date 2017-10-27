#include "stdafx.h"
#include "Server.h"

int main(int argc, char **argv)
{
    Server *server = new Server("127.0.0.1", atoi(argv[1]));
    server->start_service();
    getchar();
    return 0;
}

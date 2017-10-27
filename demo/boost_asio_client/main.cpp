#include "stdafx.h"
#include "Client.h"

int main(int argc, char **argv)
{
    //Client *client = new Client("127.0.0.1", 11001);
    Client *client = new Client(argv[1], atoi(argv[2]));
    client->start_work();
    getchar();
    delete client;
    return 0;
}

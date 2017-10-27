/*
 *  COPYRIGHT NOTICE
 *  Copyright (c) 2015, Douyu Network Technology Co., Ltd. in Wuhan
 *  All rights reserved.
 *
 *  @version : 1.0
 *  @author : mxl
 *  @E-mail：xiaolongicx@gmail.com
 *  @date : 2015/5/19
 *
 *  Revision Notes :
*/

#include "dy_barrage_client.h"
#include <iostream>
#include <string>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

using namespace std;

void usage()
{
    cout << "usage:" << endl;
    cout << "\t./get_dy_barrage host port room_id" << endl;
}

void *thr_keep_live(void *args)
{
    dy_barrage_client *dy_bclient = (dy_barrage_client *)args;
    while(1)
    {
        //cout << "begin to keep live" << endl;

        dy_bclient->keep_alive();
        sleep(45);      //keep live once per 45 seconds
    }
}

int main(int argc, char **args)
{
    int ret = 0;
    int room_id = 0;
    int32_t port = 0;
    string host;

    if(argc < 4)
    {
        usage();
        return 0;
    }

    // parse parameters
    host.assign(args[1]);
    port = atoi(args[2]);
    room_id = atoi(args[3]);

    //cout << host << ":" << port << endl;

    dy_barrage_client dy_bclient;

    ret = dy_bclient.connect_dy_server(host.c_str(), port);
    if(0 != ret)
    {
        cout << "please check the address and restart the program" << endl;
        return 0;
    }

    ret = dy_bclient.login_dy_room();
    if(0 != ret)
    {
        return 0;
    }

    ret = dy_bclient.join_dy_room_group(room_id, -9999);
     if(0 != ret)
    {
        return 0;
    }

    // create a thread to keep alive
    pthread_t tid;
    ret = pthread_create(&tid, NULL, thr_keep_live, &dy_bclient);
    if(ret != 0)
    {
        cout << "Create pthread error!" << endl;
        return 0;
    }

    while(1)
    {
        dy_bclient.get_dy_server_msg();
    }

    pthread_join(tid, NULL);

    return 0;
}

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

#include "data_def.h"
#include "dy_barrage_client.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <iostream>

using namespace std;

#define MAX_DATA_SIZE 4096   //maximum length(bytes) of each reception

dy_barrage_client::dy_barrage_client()
{
}

dy_barrage_client::~dy_barrage_client()
{
}

int dy_barrage_client::connect_dy_server(const char *host_p, int port)
{
    struct hostent *host;
    struct sockaddr_in serv_addr;

    host = gethostbyname(host_p);
    if (host == NULL)
    {
        cout << "gethostbyname err, host is" << host_p << endl;
        return -1;
    }

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd == -1)
    {
        cout << "create socket failed!" << endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr = *((struct in_addr *)host->h_addr);
    bzero(&(serv_addr.sin_zero), 8);

    int con_ret = connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr));
    if(con_ret == -1)
    {
        cout << "connect server " << host_p << ":" << port << " err!" << endl;
        return -1;
    }
    else
    {
        cout << "connect server " << host_p << ":" << port << " ok" << endl;
    }

    return 0;
}

int dy_barrage_client::login_dy_room()
{
    int ret = 0;
    dy_login_req login_req;
    string data = login_req.transform_to_dy_string();

    //cout << data << endl;

    ret = send(sock_fd, data.data(), data.size(), 0);
    if(ret == -1)
    {
        cout << "send login request err: " << ret << endl;
    }
    else
    {
        cout << "send login request ok" << endl;
    }

    char buf[MAX_DATA_SIZE] = {0};
    int recv_bytes = recv(sock_fd, buf, MAX_DATA_SIZE, 0);
    if(recv_bytes == -1)
    {
        cout << "receive login request err!" << endl;
        return -1;
    }
    else
    {
        dy_login_res login_res;
        login_res.parse_from_dy_string(string(buf, recv_bytes));

        if (0 == login_res.ret)
        {
            cout << "login successfully" << endl;
        }
        else
        {
            cout << "login err: " << login_res.ret << endl;
        }
    }

    return 0;
}

int dy_barrage_client::join_dy_room_group(int room_id, int group_id)
{
    int ret = 0;

    dy_join_group_req join_req(room_id, group_id);

    string data = join_req.transform_to_dy_string();

    ret = send(sock_fd, data.data(), data.size(), 0);
    if(ret == -1)
    {
        cout << "send join group request err: " << ret << endl;
    }
    else
    {
        cout << "send join group ok" << endl;
    }

    return 0;
}

void dy_barrage_client::get_dy_server_msg()
{
    char buf[MAX_DATA_SIZE] = {0};
    int recv_bytes = recv(sock_fd, buf, MAX_DATA_SIZE, 0);
    if(recv_bytes == -1)
    {
        cout << "receive server message err!" << endl;
        return;
    }
    else
    {
        //you should better paste the packet as douyu packet header length, if not something unpredictable may happen
        string pack_data(buf, recv_bytes);
        int msg_type = get_dy_msg_type(pack_data);

        switch(msg_type)
        {
            case MSG_TYPE_BARRAGE:
                on_barrage(pack_data);
                break;
            // deal other server message as you need here
            default:
                break;
        }
    }
}

void dy_barrage_client::keep_alive()
{
    dy_keep_alive_req keepl_req(time(NULL));

    string data = keepl_req.transform_to_dy_string();

    int ret = send(sock_fd, data.data(), data.size(), 0);
    if(ret == -1)
    {
        cout << "send keep alive request err: " << ret << endl;
    }
    /*
    else
    {
        cout << "send keep alive ok" << endl;
    }
    */
}

void dy_barrage_client::on_barrage(string data)
{
    dy_barrage_res barr_res;
    barr_res.parse_from_dy_string(data);

    cout << barr_res.sender_name << ": " << barr_res.content << endl;
}

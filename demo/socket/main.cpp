#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <iostream>

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        std::cout<< "usage ./mian host port" << std::endl;
        exit(0);
    }


    int sockfd;
    unsigned short port;
    in_addr_t addr_in;
    struct sockaddr_in ser_addr;
    int len = 0;
    char send_buf[1024];
    char recv_buf[1024];

    std::string host(argv[1]);

    port = atoi(argv[2]);

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(-1 == sockfd)
    {
        perror("Failed to sockfd");
        return -1;
    }

    memset(&ser_addr,0,sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    //ser_addr.sin_port = htons(10003);
    ser_addr.sin_port = htons(port);
    //ser_addr.sin_addr.s_addr = inet_addr("192.168.1.64");
    ser_addr.sin_addr.s_addr = inet_addr(host.c_str());
    if(-1 == connect(sockfd,(struct sockaddr *)&ser_addr,sizeof(ser_addr)))
    {
        perror("Failed to connect");
        return -1;
    }

    memset(send_buf,0,sizeof(send_buf));

    printf("len:%d\n", strlen("type@=loginreq/username@=auto_y91gJJ6cBh/password@=e10adc3949ba59abbe56e057f20f883e/roompass@=/roomid@=396/devid@=E55DE360979A27D9CFBBFE671456BFB2/rt@=1424936507/vk@=8841f175581ac4454eb2b60040e692a6/"));

    send_buf[0] = 0xd0;
    //send_buf[0] = 0x00;
    send_buf[1] = 0x00;
    send_buf[2] = 0x00;
    send_buf[3] = 0x00;

    //send_buf[4] = 0x00;
    send_buf[4] = 0xd0;
    send_buf[5] = 0x00;
    send_buf[6] = 0x00;
    send_buf[7] = 0x00;

    send_buf[8] = 0xb1;
    send_buf[9] = 0x02;
    send_buf[10] = 0x00;
    send_buf[11] = 0x00;

    sprintf(&send_buf[12], "type@=loginreq/username@=auto_y91gJJ6cBh/password@=e10adc3949ba59abbe56e057f20f883e/roompass@=/roomid@=192/devid@=E55DE360979A27D9CFBBFE671456BFB2/rt@=1424939165/vk@=a7094a3e5d8d86069e73371cec04a171/");
    len = send(sockfd, send_buf,strlen(&send_buf[12]) + 12 + 1, 0);
    //len = send(sockfd, send_buf,strlen(&send_buf[0]), 0);
    printf("send len:%d\n", len);
    if(-1 ==len)
    {
        perror("Failed to send");
        return -1;
    }

    printf("Now recv...\n");
    memset(recv_buf, 0 ,sizeof(recv_buf));
    printf("%s\n", recv_buf);
    len = recv(sockfd, recv_buf, sizeof(recv_buf), 0);
    if(-1 == len)
    {
        perror("Failed to recv");
        return -1;
    }

    printf("Receive message:%s\n", &recv_buf[12]);
    //close(sockfd);
    shutdown(sockfd, SHUT_WR);

    printf("Now recv agagin...\n");
    memset(recv_buf, 0 ,sizeof(recv_buf));
    printf("%s\n", recv_buf);
    len = recv(sockfd, recv_buf, sizeof(recv_buf), 0);
    if(-1 == len)
    {
        perror("Failed to recv");
        return -1;
    }

    printf("Receive message:%s\n", &recv_buf[12]);

    printf("Now recv agagin2...\n");
    memset(recv_buf, 0 ,sizeof(recv_buf));
    printf("%s\n", recv_buf);
    len = recv(sockfd, recv_buf, sizeof(recv_buf), 0);
    if(-1 == len)
    {
        perror("Failed to recv");
        return -1;
    }

    printf("Receive message:%s\n", &recv_buf[12]);

    return 0;
}

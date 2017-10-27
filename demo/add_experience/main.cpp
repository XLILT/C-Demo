/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年12月16日 14时16分49秒
 *       Revision:  none
 *       Compiler:  clang++
 *
 *         Author:  wangfei (wangfei@douyu.tv)
 *		  Company:  武汉斗鱼网络科技有限公司
 *
 * =====================================================================================
 */
#include "stdafx.h"

#include "CompleteServer.h"

int main(int argc, char **argv)
{
    Stt::DB::MySQLConnection::MySQL_Init();
    
    dy::complete_user_exp::CompleteServer *server = new dy::complete_user_exp::CompleteServer;
    if(server->create() == false)
    {
        printf("Fail to create CompleteServer!!!\n");
        delete server;
        server = NULL;
    }
    else
    {
        printf("Succeed in creating CompleteServer!!!\n");
    }

    if(0 != server->execute())
    {
        printf("Failed to execute, please go to check the logs.\n");
    }
    else
    {
        printf("Succeed in executing!\n");
    }

    sleep(2);

    Stt::DB::MySQLConnection::MySQL_End();

    return 0;
}

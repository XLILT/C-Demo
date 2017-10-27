#include <unistd.h>  
#include <signal.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <sys/resource.h>  
#include "stdafx.h"

void init()  
{  
    int pid;  
    int i;  
    struct rlimit   rl;                       //获取进程资源西限制  
  
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)    //获取进程最多文件数  
            printf(":can't get file limit");  
  
    if((pid = fork()) != 0)  
        exit(0);                          //父进程，退出  
  
    else if(pid < 0)                          //开辟进程失败，退出并关闭所有进程  
        exit(1);  
    /* 子进程继续执行 */  
    setsid();                               //创建新的会话组，子进程成为组长，并与控制终端分离  
  
    /* 防止子进程（组长）获取控制终端 */  
    if((pid = fork()) != 0)  
        exit(0);                       //父进程，退出  
  
    else if(pid < 0)   
           exit(1);                        //开辟进程失败，退出并关闭所有进程  
  
/* 第二子进程继续执行 , 第二子进程不再是会会话组组长*/  
  
    /* 关闭打开的文件描述符*/  
    if (rl.rlim_max == RLIM_INFINITY)     //RLIM_INFINITY是一个无穷量的限制        
             rl.rlim_max = 1024;  
        for (i = 0; i < (int)rl.rlim_max; i++)  
             close(i);  
       
    umask(0);       // 重设文件创建掩码   
    return;  
}

void f()
{
	while(1)
	{
		FILE *pp = popen("ps -eo pid,tid,comm,%cpu >> program_f.log", "r");
	        pclose(pp);
        	sleep(2);
	}
}

int main()  
{  
    signal(SIGCHLD, SIG_IGN); // 忽略子进程结束信号，防止出现僵尸进程   
    //boost::thread *m_thread = 
   	
    init();
    new boost::thread(boost::bind(&f));

    while(1)
    {
	FILE *pp = popen("ps -eo pid,tid,comm,%cpu >> program.log", "r");
	pclose(pp);
	sleep(2);
    }

    return 0;
}

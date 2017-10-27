/* 
 * File:   SlaveServer.h
 * Author: zhang
 *
 * Created on 2015年7月25日, 上午12:04
 */

#ifndef SLAVESERVER_H_234523452
#define	SLAVESERVER_H_234523452


#include <CommonBase/TaskQueue.h>
#include <CommonBase/ThreadTool.h>
#include <CommonBase/ThreadingMsgQueue.h>
#include <CommonBase/BaseBuffer.h>
#include <CommonBase/TransmitData.h>
#include <CommonBase/netmsg.h>
#include <CommonBase/AsyncQueue.h>
#include <CommonBase/TimerTask.h>

#include <boost/unordered_set.hpp>
#include <vector>

#include "NetServer.h"

#pragma once

class SlaveSession;
class SlaveSessionSet;


//单线程的消息循环，帮主线程分担业务压力
class SlaveServer {
public:
    SlaveServer();
    SlaveServer(const SlaveServer& orig);
    virtual ~SlaveServer();
    
    virtual bool create(SttSTNetServer * _master_server);  //此函数运行在控制线程,可能会长时间卡住
	virtual void destory(); //此函数运行在控制线程,可能会长时间卡住

    ///在主线程队列里执行一个任务,线程安全
	virtual void queue_task(TaskRunCallback& t, 
                           const char * src_info = NULL, const char * hint = NULL, const int exec_time_limit = -1);
    
    /// 入队一个异步执行任务,线程安全
	virtual void aysnc_queue_task(TaskRunCallback & pMsg); 
    
    //添加一个定时任务
	virtual int  add_timer_task(TaskRunCallback& pMsg, int nInterval, int nLoopCount = -1, bool bRunImmediately = false, SttTaskQueue * queue = NULL,
                 const char * src_info = NULL, const char * hint = NULL, const int exec_time_limit = -1);  
    
    //移除一个定时任务
	virtual void remove_timer_task(int task_id);  

    int   slave_server_id; //进程内部的服务id
    char  slave_server_name[256]; //进程内部的服务名称
private:

    SttTaskQueue *      main_queue;
	boost::thread *		mainproc_thread;
	volatile bool		is_stop;
    SttSTNetServer *    master_server;

	void  main_proc();

////////////////////////  统计相关  //////////////////////////////////////////////////
public:
    volatile int64_t m_last_stat_time;           //上次计时
	volatile int64_t m_stat_recv_all_msg_count;  //接收的消息总数
	volatile int64_t m_stat_recv_all_msg_len;    //接收的消息总长度
	volatile int64_t m_stat_recv_min_msg_count;  //过去一分钟内接收的消息数
	volatile int64_t m_stat_recv_min_msg_len;    //过去一分钟内接收的消息长度

	volatile int64_t m_stat_send_all_msg_count;  //发送的消息总数
	volatile int64_t m_stat_send_all_msg_len;
	volatile int64_t m_stat_send_min_msg_count;
	volatile int64_t m_stat_send_min_msg_len;

	volatile int64_t m_stat_asio_exec_all_count;  //asio操作总数
	volatile int64_t m_stat_asio_exec_min_count;

	volatile int64_t m_stat_net_error_all_count;  //网络错误总数
	volatile int64_t m_stat_net_error_min_count;

	volatile int64_t m_stat_task_exec_all_count;   //任务队列执行总数
	volatile int64_t m_stat_task_exec_min_count;

	volatile int64_t m_stat_asyn_task_exec_all_count;  //异步任务总数
	volatile int64_t m_stat_asyn_task_exec_min_count;

	volatile int64_t m_stat_new_connection_all_count;   //创建连接总数
	volatile int64_t m_stat_new_connection_min_conut;
	volatile int64_t m_stat_del_connection_all_count;   //销毁连接总数
	volatile int64_t m_stat_del_connection_min_count;

	volatile int64_t m_stat_main_proc_all_time;         //主线程消耗时间
	volatile int64_t m_stat_main_proc_min_time;
	volatile int64_t m_stat_main_proc_min_max_per_time; //一分钟内单次最大时间
	volatile int64_t m_stat_main_proc_min_loop_count;
	volatile int64_t m_stat_main_proc_min_sleep_count;
	volatile int64_t m_stat_main_proc_min_asio_time;
	volatile int64_t m_stat_main_proc_min_max_asio_per_time; //一分钟内单次最大时间
	volatile int64_t m_stat_main_proc_min_task_time;
	volatile int64_t m_stat_main_proc_min_max_task_per_time; //一分钟内单次最大时间
};

#endif	/* SLAVESERVER_H */


/* 
 * File:   SlaveServer.cpp
 * Author: zhang
 * 
 * Created on 2015年7月25日, 上午12:04
 */
#include "sb_pch.h"
#include "SlaveServer.h"

SlaveServer::SlaveServer() {
    this->slave_server_id = 0;
    memset(this->slave_server_name, 0, sizeof(this->slave_server_name));

    this->is_stop = false;
	this->main_queue = new SttTaskQueue();
	this->mainproc_thread = new boost::thread(boost::bind(&SlaveServer::main_proc,this));
}

SlaveServer::SlaveServer(const SlaveServer& orig) {
}

SlaveServer::~SlaveServer() {
    this->is_stop = true;
	this->mainproc_thread->join();
	delete this->mainproc_thread;
	delete this->main_queue;
}

//此函数运行在控制线程,可能会长时间卡住
bool SlaveServer::create(SttSTNetServer * _master_server) {
    this->master_server = _master_server;
   
    return true;
}

//此函数运行在控制线程,可能会长时间卡住
bool SlaveServer::destory() {
    this->is_stop = true;
    return false;
}

void SlaveServer::main_proc()
{
	int count_exec = 0, idle_count = 0;

	while (!this->is_stop)
	{
		int64_t tick_start = SttGetUsTickCount();
		count_exec = 0;


		int64_t tick_start2 = tick_start;//SttGetUsTickCount();
		int64_t count2 = main_queue->ProcAllTask();   //处理Task队列
		count_exec += (int)count2;
		m_stat_task_exec_all_count += count2;
		m_stat_task_exec_min_count += count2;

		//统计执行时间
		int64_t tick_end = SttGetUsTickCount();
		int64_t tick_exec = tick_end - tick_start;
		m_stat_main_proc_all_time += tick_exec;
		m_stat_main_proc_min_time += tick_exec;
		if( tick_exec > m_stat_main_proc_min_max_per_time) 
		{
			m_stat_main_proc_min_max_per_time = tick_exec;
		}
		m_stat_main_proc_min_loop_count++;

		m_stat_main_proc_min_asio_time += tick_start2 - tick_start;
		if( tick_start2 - tick_start > m_stat_main_proc_min_max_asio_per_time) 
		{
			m_stat_main_proc_min_max_asio_per_time = tick_start2 - tick_start;
		}
        
        if( tick_start2 - tick_start > 10000)  //10ms
		{
			//TL_FAST_LOG("net_err.log", tlstDay, "asio too long: %d",(int)(tick_start2 - tick_start));
		}

		m_stat_main_proc_min_task_time += tick_end - tick_start2;
		if( tick_end - tick_start2 > m_stat_main_proc_min_max_task_per_time) 
		{
			m_stat_main_proc_min_max_task_per_time = tick_end - tick_start2;
		}
		

		if (count_exec == 0)
		{
			idle_count++;
			if (idle_count >= 10)
			{
				idle_count = 0;
				if (1)
				{
					SttSleep(1);
					m_stat_main_proc_min_sleep_count++;
				}
			}
		}
	}


	do
	{
		count_exec = 0;
		count_exec += (int)main_queue->ProcAllTask();
	} while (count_exec > 0);   //处理剩余的网络收发和Task
}


void SlaveServer::queue_task( TaskRunCallback& t, const char * src_info, const char * hint, const int exec_time_limit )
{
	main_queue->QueueTask(t, src_info, hint, exec_time_limit);
}

void SlaveServer::aysnc_queue_task( TaskRunCallback & pTask)
{
    this->master_server->AysncQueue(pTask);

}

int SlaveServer::add_timer_task(TaskRunCallback& pMsg, int nInterval, int nLoopCount, bool bRunImmediately, SttTaskQueue * queue,
                                   const char * src_info, const char * hint, const int exec_time_limit)
{
	return this->master_server->add_timer_task(pMsg, nInterval, nLoopCount, bRunImmediately, queue, src_info, hint, exec_time_limit);
}

void SlaveServer::remove_timer_task(int task_id)
{
	this->master_server->remove_timer_task(task_id);
}
/* 
 * File:   SlaveServer.h
 * Author: zhang
 *
 * Created on 2015��7��25��, ����12:04
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


//���̵߳���Ϣѭ���������̷ֵ߳�ҵ��ѹ��
class SlaveServer {
public:
    SlaveServer();
    SlaveServer(const SlaveServer& orig);
    virtual ~SlaveServer();
    
    virtual bool create(SttSTNetServer * _master_server);  //�˺��������ڿ����߳�,���᳤ܻʱ�俨ס
	virtual void destory(); //�˺��������ڿ����߳�,���᳤ܻʱ�俨ס

    ///�����̶߳�����ִ��һ������,�̰߳�ȫ
	virtual void queue_task(TaskRunCallback& t, 
                           const char * src_info = NULL, const char * hint = NULL, const int exec_time_limit = -1);
    
    /// ���һ���첽ִ������,�̰߳�ȫ
	virtual void aysnc_queue_task(TaskRunCallback & pMsg); 
    
    //���һ����ʱ����
	virtual int  add_timer_task(TaskRunCallback& pMsg, int nInterval, int nLoopCount = -1, bool bRunImmediately = false, SttTaskQueue * queue = NULL,
                 const char * src_info = NULL, const char * hint = NULL, const int exec_time_limit = -1);  
    
    //�Ƴ�һ����ʱ����
	virtual void remove_timer_task(int task_id);  

    int   slave_server_id; //�����ڲ��ķ���id
    char  slave_server_name[256]; //�����ڲ��ķ�������
private:

    SttTaskQueue *      main_queue;
	boost::thread *		mainproc_thread;
	volatile bool		is_stop;
    SttSTNetServer *    master_server;

	void  main_proc();

////////////////////////  ͳ�����  //////////////////////////////////////////////////
public:
    volatile int64_t m_last_stat_time;           //�ϴμ�ʱ
	volatile int64_t m_stat_recv_all_msg_count;  //���յ���Ϣ����
	volatile int64_t m_stat_recv_all_msg_len;    //���յ���Ϣ�ܳ���
	volatile int64_t m_stat_recv_min_msg_count;  //��ȥһ�����ڽ��յ���Ϣ��
	volatile int64_t m_stat_recv_min_msg_len;    //��ȥһ�����ڽ��յ���Ϣ����

	volatile int64_t m_stat_send_all_msg_count;  //���͵���Ϣ����
	volatile int64_t m_stat_send_all_msg_len;
	volatile int64_t m_stat_send_min_msg_count;
	volatile int64_t m_stat_send_min_msg_len;

	volatile int64_t m_stat_asio_exec_all_count;  //asio��������
	volatile int64_t m_stat_asio_exec_min_count;

	volatile int64_t m_stat_net_error_all_count;  //�����������
	volatile int64_t m_stat_net_error_min_count;

	volatile int64_t m_stat_task_exec_all_count;   //�������ִ������
	volatile int64_t m_stat_task_exec_min_count;

	volatile int64_t m_stat_asyn_task_exec_all_count;  //�첽��������
	volatile int64_t m_stat_asyn_task_exec_min_count;

	volatile int64_t m_stat_new_connection_all_count;   //������������
	volatile int64_t m_stat_new_connection_min_conut;
	volatile int64_t m_stat_del_connection_all_count;   //������������
	volatile int64_t m_stat_del_connection_min_count;

	volatile int64_t m_stat_main_proc_all_time;         //���߳�����ʱ��
	volatile int64_t m_stat_main_proc_min_time;
	volatile int64_t m_stat_main_proc_min_max_per_time; //һ�����ڵ������ʱ��
	volatile int64_t m_stat_main_proc_min_loop_count;
	volatile int64_t m_stat_main_proc_min_sleep_count;
	volatile int64_t m_stat_main_proc_min_asio_time;
	volatile int64_t m_stat_main_proc_min_max_asio_per_time; //һ�����ڵ������ʱ��
	volatile int64_t m_stat_main_proc_min_task_time;
	volatile int64_t m_stat_main_proc_min_max_task_per_time; //һ�����ڵ������ʱ��
};

#endif	/* SLAVESERVER_H */


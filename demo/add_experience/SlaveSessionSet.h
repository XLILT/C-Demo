/* 
 * File:   SlaveSessionSet.h
 * Author: zhang
 *
 * Created on 2015��7��25��, ����1:03
 */

#ifndef SLAVESESSIONSET_H_524524353
#define	SLAVESESSIONSET_H_524524353


#pragma once




#include "SlaveServer.h"

class SlaveSession;
class SttSessionSet;
class SlaveServer;


class SlaveSessionSet {
public:
    SlaveSessionSet();
    SlaveSessionSet(const SlaveSessionSet& orig);
    virtual ~SlaveSessionSet();
    
	virtual bool create(SlaveServer * server);

	virtual void QueueSessionSetMsg(TaskRunCallback& task, const char* perfomance_info = NULL);

	///��Session��ӵ���Set��,�˺���ֻ��������Session����Set�ı�Ҫ������Session����󣬻����OnSessionEnter���������ˡ�
	virtual bool add_session( SlaveSession * session );

	///��Session�Ƴ�Set,�˺���ֻ��������Session�Ƴ�Set�ı�Ҫ������Session�Ƴ��󣬻����OnSessionLeave���������ˡ�
	virtual bool remove_session( SlaveSession *session );


	virtual void on_session_enter(SlaveSession *session); /// Session����ĺ�̴���һ����Ҫ�������м̳У������IP���ܵȵȡ�


	virtual void On_session_leave(SlaveSession *session); ///Session�뿪�ĺ�̴���һ����Ҫ�������м̳С�


	bool broadcast_msg(CSttTransmitData* data, SlaveSession* except_session = NULL); /// ��SessionSet�й㲥��Ϣ, pExceptSession Ҫ�ų���Session

	bool broadcast_msg(MessageBase* pMsg, SlaveSession* except_session = NULL); /// ��SessionSet�й㲥��Ϣ, pExceptSession Ҫ�ų���Session

	bool ExistSession(SlaveSession * session);  ///���Session�Ƿ񻹴��ڴ��߳�
    
    void check_kick_session(SlaveSession * session, int err_code); //��ȫ��Kickһ��session,��Ҫ��kickǰ����session�Ƿ񻹴���


	virtual void Destory_Notify(int err_code = ET_ServerClosed); //֪ͨ��Set�������ٲ������˺�����ֹ������������ݾ�����Ҫ���������ء�
	virtual bool IsDestoryed();    //����Ƿ��Ѿ����١�������ݾ�����Ҫ���������ء�


	SlaveServer * slave_server;

	CSttAtomCount m_WaitCount;  //���SessionSet����������첽����������������첽����û���ǰ�������ٴ˶��󣬷�ֹ���ʳ���

	typedef boost::unordered_map<int, SlaveSession*> SessionIDPtrMap;

	typedef boost::unordered_map<SlaveSession*, SlaveSession*> SessionPtrPtrMap;

	SessionIDPtrMap m_IDMap;    ///����Session ID��ָ���ӳ��
	SessionPtrPtrMap m_PtrMap;  ///��Ҫ�����ж�һ��ָ���Ƿ�����ڱ�Set

 
private:

};

#endif	/* SLAVESESSIONSET_H */


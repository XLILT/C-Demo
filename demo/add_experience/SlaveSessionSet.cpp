/* 
 * File:   SlaveSessionSet.cpp
 * Author: zhang
 * 
 * Created on 2015年7月25日, 上午1:03
 */

#include "SlaveServer.h"
#include "SlaveSessionSet.h"
#include "SlaveSession.h"

SlaveSessionSet::SlaveSessionSet():slave_server(NULL), m_WaitCount(0)
{
}

SlaveSessionSet::SlaveSessionSet(const SlaveSessionSet& orig) 
{
}

SlaveSessionSet::~SlaveSessionSet() 
{
}

bool SlaveSessionSet::create(SlaveServer * server)
{
	this->m_IDMap.clear();
	this->m_PtrMap.clear();
	this->slave_server = server;
	return true;
}

void SlaveSessionSet::QueueSessionSetMsg(TaskRunCallback& task, const char* perfomance_info)
{
	this->slave_server->queue_task(task, perfomance_info);
}

bool SlaveSessionSet::add_session( SlaveSession * session )
{
	SlaveSession*& u = this->m_IDMap[session->sessiong_id];
	assert(u == NULL);  //TODO：断线重连情况下存在相同SessID，未处理
	//if(u != NULL)
	//{
	//	u->kick();
	//	session->kick();
	//	return false;
	//}


	session->slave_session_set = this;
	u = session;
	this->m_PtrMap[session] = session;

	//assert(session->status != SttSession::SS_EXIT);
	if(session->status == SttSession::SS_EXIT)  //此Session已是退出状态？ 在从Pool到Set的过程中被Kick了
	{
		TL_PRINTF("Default", tllDebug, "status == SttSession::SS_EXIT %p, %p, %d ", this, session, session->sessiong_id);
		session->kick();
		return false;
	}

	this->on_session_enter(session);
	return true;
}

bool SlaveSessionSet::remove_session( SlaveSession *session )
{
	assert(session->slave_session_set == this); //此Session已经在其它容器中？

	if(this->m_PtrMap.find(session) != this->m_PtrMap.end())
	{
		this->m_IDMap.erase(session->sessiong_id);
		this->m_PtrMap.erase(session);
		session->slave_session_set = NULL;
	}
	else
	{
		assert(0);
	}

	this->On_session_leave(session);
	return true;
}

void SlaveSessionSet::on_session_enter(SlaveSession *session)
{
	session->status  = SttSession::SS_NORMAL;
	return ;
}

void SlaveSessionSet::On_session_leave(SlaveSession *session)
{
	return;
}

bool SlaveSessionSet::broadcast_msg(CSttTransmitData* data, SlaveSession* except_session/* = NULL*/)
{
	SessionPtrPtrMap::const_iterator hm1;
	for (hm1 = this->m_PtrMap.begin(); hm1 != this->m_PtrMap.end(); hm1++)
	{
		SlaveSession* pSession = hm1->second;
		if (pSession == except_session)
		{
			continue;
		}
		pSession->send_msg(data);
	}
	return true;
}

bool SlaveSessionSet::broadcast_msg(MessageBase* pMsg, SlaveSession* except_session/* = NULL*/)
{
	CSttTransmitData* data = BuildMsgData(pMsg);
	bool b = broadcast_msg(data, except_session);
	data->Release();
	return b;
}

bool SlaveSessionSet::SlaveSessionSet::ExistSession(SlaveSession * session)
{
	if(this->m_PtrMap.find(session) != this->m_PtrMap.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void SlaveSessionSet::check_kick_session(SlaveSession * session, int err_code)
{
	return;
}

void SlaveSessionSet::Destory_Notify(int err_code)
{
	SessionPtrPtrMap::const_iterator hm1;
	for (hm1 = this->m_PtrMap.begin(); hm1 != this->m_PtrMap.end(); hm1++)
	{
		SlaveSession* pSession = hm1->second;
		pSession->kick(err_code);
	}
}

bool SlaveSessionSet::IsDestoryed()
{
	if (this->m_PtrMap.size() == 0  &&  this->m_WaitCount == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


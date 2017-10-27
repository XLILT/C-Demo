/* 
 * File:   SlaveSession.cpp
 * Author: zhang
 * 
 * Created on 2015年7月25日, 上午1:02
 */

#include "SlaveSession.h"
#include "SlaveSessionSet.h"
#include "SlaveServer.h"

static CSttAtomCount g_last_session_id(0);

SlaveSession::SlaveSession():status(SS_NONE), last_active(0), slave_session_set(NULL),
	slave_server(NULL), m_Kicked(0), connection(NULL), m_WaitCount(0)
{
	this->sessiong_id = ++g_last_session_id;
}

SlaveSession::SlaveSession(const SlaveSession& orig) 
{
}

SlaveSession::~SlaveSession() 
{
}

bool SlaveSession::Create(ISttConnection * new_connection, SlaveSessionSet * session_set)
{
	new_connection->AddRef();

	this->slave_server = slave_session_set->slave_server;
	this->connection = new_connection;
	this->connection->RegRecvCallback(boost::bind(&SlaveSession::queue_recv_msg, this, _1));
	this->connection->RegErrorCallback(boost::bind(&SlaveSession::OnSocketError, this, _1));
	this->last_active = SttGetTickCount();

	return true;
}


//此函数运行在ASIO工作线程
void SlaveSession::queue_recv_msg(const MessageBase* pMsgBuf)
{
	if(NULL == this->slave_session_set)
	{
		return;
	}
	
	this->last_active = SttGetTickCount();
	CSttTransmitData* pData = new CSttTransmitData(pMsgBuf, pMsgBuf->m_Size);  //pData在Msg_RecvMsg中Release();
	MsgRunCallback b = boost::bind(&SlaveSession::QMsg_RecvMsg, this, pData);
	this->slave_session_set->QueueSessionSetMsg(b, SRC_INFO());

	return;
}

void SlaveSession::excute_msg(MessageBase* pMsgBuf)
{
	return;
}

void SlaveSession::OnSocketError(const boost::system::error_code& error)
{
	this->slave_server->m_stat_net_error_all_count++;
	this->slave_server->m_stat_net_error_min_count++;
	this->kick(ET_BadError);
	return;
}

void SlaveSession::destroy()
{
	this->connection->Close();
	this->connection->Release();
	this->connection = NULL;
	return;
}

bool SlaveSession::can_release()
{
	if(this->m_WaitCount > 0)
	{
		return false;
	}
	return true;
}

void SlaveSession::kick(int err_code = 0)
{
	if(++(this->m_Kicked) > 1)//防止多次执行kick
	{
		return;
	}

	this->connection->StopRecv();

	if(err_code != 0)
	{
		MS_Error * pError = MS_Error::Alloc(err_code);
		this->send_msg(pError);
		delete[] (char*)pError;
	}

	this->status = SttSession::SS_EXIT;
	this->on_kick();

	TaskRunCallback t = boost::bind(&SlaveSession::do_kick(), this);
	this->slave_session_set->QueueSessionSetMsg(t, SRC_INFO());

	return;
}

void SlaveSession::do_kick()
{
	if(this->can_release())
	{
		this->slave_session_set->remove_session(this);
		this->destroy();
		this->slave_server->m_stat_del_connection_all_count++;
		this->slave_server->m_stat_del_connection_min_count++;
		delete this;
	}
	else
	{
		TaskRunCallback t = boost::bind(&SlaveSession::TM_DoKick, this);
		this->slave_server->add_timer_task(t, 1*1000, 1);
	}

	return;
}

void SlaveSession::TM_DoKick()
{
	TaskRunCallback t = boost::bind(&SlaveSession::do_kick, this);
	this->slave_session_set->QueueSessionSetMsg(t, SRC_INFO());
	return;
}

void SlaveSession::on_kick()
{
	return;
}

bool SlaveSession::send_msg(MessageBase* msg)
{
	CSttTransmitData* data = BuildMsgData(msg);
	this->send_msg(data);
	data->Release();
	return true;
}

bool SlaveSession::send_msg(CSttTransmitData* msg)
{
	this->slave_server->m_stat_send_all_msg_count++;
	this->slave_server->m_stat_send_all_msg_len += ((MessageBase*)msg->m_buf.GetBuffer())->m_Size;
	this->slave_server->m_stat_send_min_msg_count++;
	this->slave_server->m_stat_send_min_msg_len += ((MessageBase*)msg->m_buf.GetBuffer())->m_Size;

	this->connection->QueueSend(msg);
	return true;
}

void SlaveSession::QMsg_RecvMsg(CSttTransmitData * recvData)
{
	this->slave_server->m_stat_recv_all_msg_count++;
	this->slave_server->m_stat_recv_all_msg_len += ((MessageBase*)recvData->m_buf.GetBuffer())->m_Size;
	this->slave_server->m_stat_recv_min_msg_count++;
	this->slave_server->m_stat_recv_min_msg_len += ((MessageBase*)recvData->m_buf.GetBuffer())->m_Size;
	
	this->excute_msg((MessageBase*)recvData->m_buf.GetBuffer());
	recvData->Release();

	return;
}

void SlaveSession::enter_set(SlaveSessionSet *pSet)
{
	pSet->add_session(this);
	return;
}

void SlaveSession::leave_set(SlaveSessionSet * pNewSet = NULL)
{
	assert(this->slave_session_set != NULL);

	this->slave_session_set->remove_session(this);

	if (pNewSet != NULL)
	{
		this->slave_session_set = pNewSet;
		this->enter_set(pNewSet);
	}

	return;
}


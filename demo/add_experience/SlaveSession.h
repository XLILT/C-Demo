/* 
 * File:   SlaveSession.h
 * Author: zhang
 *
 * Created on 2015年7月25日, 上午1:02
 */

#ifndef SLAVESESSION_H_6238471032
#define	SLAVESESSION_H_6238471032

#pragma once

#include "SessionSet.h"

class ISttConnection;
class SlaveSessionSet;
class SlaveServer;
class CSttTransmitData;
class MessageBase;



class SlaveSession {
public:
    SlaveSession();
    SlaveSession(const SlaveSession& orig);
    virtual ~SlaveSession();
    
    
	virtual bool Create(ISttConnection * new_connection, SlaveSessionSet * session_set);


	/** 处理收到的网络数据   
	*    
	*     处理收到的网络数据，会将数据添加入buffer，并判断是否是一个完整的消息。如果是完整的消息，则通过调用QueueRecvMsg投递到SessionSet的消息队列里。    
	*     @param pData  传入的数据地址 
	*     @param error  错误信息    
	*     @return    无   
	*     @see    QueueRecvMsg()    （本函数参考其它的相关的函数，这里作一个链接）  
	*     @note    默认每个完整数据包的前四字节代表长度
	*/
	virtual void queue_recv_msg(const MessageBase* pMsgBuf);


	/** 执行网络消息。此函数将网络消息进行协议级的解析，并执行。需要在子类中处理。
	*    
	*     执行网络消息。    
	*     @param pMsgBuf  收到的网络消息数据指针
	*     @return    无   
	*     @note  此函数需要继承
	*/
	virtual void excute_msg(MessageBase* pMsgBuf);

	virtual void OnSocketError(const boost::system::error_code& error);

	virtual void destroy();

	/** 判断是否此Session是否可以安全销毁
	*    主要是判断关联的异步操作是否执行完
	*     @return  true或者false   
	*/
	virtual bool can_release();


	virtual void kick(int err_code = 0); //踢出此Session
    
	void do_kick();
    
	void TM_DoKick();

	virtual void on_kick();               //被踢出时的事件处理 需派生类重载
	

	virtual bool send_msg(MessageBase* msg);
	virtual bool send_msg(CSttTransmitData* msg);

	virtual void QMsg_RecvMsg(CSttTransmitData * recvData);  //SessionSet消息 处理接收到的数据



	/** 队列消息。进入指定的SessionSet
	*    
	*     进入指定的SessionSet   
	*     @param pSet  要进入的SessionSet
	*     @return    无   
	*/
	void enter_set(SlaveSessionSet *pSet);


	/** 队列消息。离开目前的SessionSet，并进入新的SessionSet。
	*    
	*     离开目前的SessionSet，并进入新的SessionSet。  
	*     @param pNewSet  要进入的SessionSet
	*     @return    无   
	*/
	void leave_set(SlaveSessionSet * pNewSet = NULL);

	int sessiong_id;
	SESSION_STATUS status;


	uint64_t last_active;

	SlaveSessionSet * slave_session_set;

	SlaveServer * slave_server;

	CSttAtomCount m_Kicked;

	ISttConnection * connection;


	//与次Session对象关联的异步操作的数量，相关异步操作没完成前不能销毁此对象，防止访问出错。
	CSttAtomCount m_WaitCount;

    
private:

};

#endif	/* SLAVESESSION_H */


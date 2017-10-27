/* 
 * File:   SlaveSession.h
 * Author: zhang
 *
 * Created on 2015��7��25��, ����1:02
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


	/** �����յ�����������   
	*    
	*     �����յ����������ݣ��Ὣ���������buffer�����ж��Ƿ���һ����������Ϣ���������������Ϣ����ͨ������QueueRecvMsgͶ�ݵ�SessionSet����Ϣ�����    
	*     @param pData  ��������ݵ�ַ 
	*     @param error  ������Ϣ    
	*     @return    ��   
	*     @see    QueueRecvMsg()    ���������ο���������صĺ�����������һ�����ӣ�  
	*     @note    Ĭ��ÿ���������ݰ���ǰ���ֽڴ�����
	*/
	virtual void queue_recv_msg(const MessageBase* pMsgBuf);


	/** ִ��������Ϣ���˺�����������Ϣ����Э�鼶�Ľ�������ִ�С���Ҫ�������д���
	*    
	*     ִ��������Ϣ��    
	*     @param pMsgBuf  �յ���������Ϣ����ָ��
	*     @return    ��   
	*     @note  �˺�����Ҫ�̳�
	*/
	virtual void excute_msg(MessageBase* pMsgBuf);

	virtual void OnSocketError(const boost::system::error_code& error);

	virtual void destroy();

	/** �ж��Ƿ��Session�Ƿ���԰�ȫ����
	*    ��Ҫ���жϹ������첽�����Ƿ�ִ����
	*     @return  true����false   
	*/
	virtual bool can_release();


	virtual void kick(int err_code = 0); //�߳���Session
    
	void do_kick();
    
	void TM_DoKick();

	virtual void on_kick();               //���߳�ʱ���¼����� ������������
	

	virtual bool send_msg(MessageBase* msg);
	virtual bool send_msg(CSttTransmitData* msg);

	virtual void QMsg_RecvMsg(CSttTransmitData * recvData);  //SessionSet��Ϣ ������յ�������



	/** ������Ϣ������ָ����SessionSet
	*    
	*     ����ָ����SessionSet   
	*     @param pSet  Ҫ�����SessionSet
	*     @return    ��   
	*/
	void enter_set(SlaveSessionSet *pSet);


	/** ������Ϣ���뿪Ŀǰ��SessionSet���������µ�SessionSet��
	*    
	*     �뿪Ŀǰ��SessionSet���������µ�SessionSet��  
	*     @param pNewSet  Ҫ�����SessionSet
	*     @return    ��   
	*/
	void leave_set(SlaveSessionSet * pNewSet = NULL);

	int sessiong_id;
	SESSION_STATUS status;


	uint64_t last_active;

	SlaveSessionSet * slave_session_set;

	SlaveServer * slave_server;

	CSttAtomCount m_Kicked;

	ISttConnection * connection;


	//���Session����������첽����������������첽����û���ǰ�������ٴ˶��󣬷�ֹ���ʳ���
	CSttAtomCount m_WaitCount;

    
private:

};

#endif	/* SLAVESESSION_H */


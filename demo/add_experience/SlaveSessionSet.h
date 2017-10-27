/* 
 * File:   SlaveSessionSet.h
 * Author: zhang
 *
 * Created on 2015年7月25日, 上午1:03
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

	///将Session添加到此Set中,此函数只单纯负责将Session放入Set的必要操作。Session进入后，会调用OnSessionEnter处理后继事宜。
	virtual bool add_session( SlaveSession * session );

	///将Session移出Set,此函数只单纯负责将Session移出Set的必要操作。Session移出后，会调用OnSessionLeave处理后继事宜。
	virtual bool remove_session( SlaveSession *session );


	virtual void on_session_enter(SlaveSession *session); /// Session进入的后继处理，一般需要在子类中继承，比如封IP功能等等。


	virtual void On_session_leave(SlaveSession *session); ///Session离开的后继处理，一般需要在子类中继承。


	bool broadcast_msg(CSttTransmitData* data, SlaveSession* except_session = NULL); /// 在SessionSet中广播消息, pExceptSession 要排除的Session

	bool broadcast_msg(MessageBase* pMsg, SlaveSession* except_session = NULL); /// 在SessionSet中广播消息, pExceptSession 要排除的Session

	bool ExistSession(SlaveSession * session);  ///检查Session是否还存在此线程
    
    void check_kick_session(SlaveSession * session, int err_code); //安全的Kick一个session,主要是kick前检查此session是否还存在


	virtual void Destory_Notify(int err_code = ET_ServerClosed); //通知此Set进行销毁操作，此函数禁止阻塞。子类根据具体需要，进行重载。
	virtual bool IsDestoryed();    //检测是否已经销毁。子类根据具体需要，进行重载。


	SlaveServer * slave_server;

	CSttAtomCount m_WaitCount;  //与次SessionSet对象关联的异步操作的数量，相关异步操作没完成前不能销毁此对象，防止访问出错。

	typedef boost::unordered_map<int, SlaveSession*> SessionIDPtrMap;

	typedef boost::unordered_map<SlaveSession*, SlaveSession*> SessionPtrPtrMap;

	SessionIDPtrMap m_IDMap;    ///保存Session ID和指针的映射
	SessionPtrPtrMap m_PtrMap;  ///主要用于判定一个指针是否存在于本Set

 
private:

};

#endif	/* SLAVESESSIONSET_H */


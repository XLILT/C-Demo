// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once
#include <stdio.h>

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include <list>
#include <vector>

#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <boost/thread.hpp>
#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <boost/timer.hpp>

#include <MySqlDB/DBCommon.h>
#include <MySqlDB/MySqlZDB.h>
#include <MySqlDB/AdoHelper.h>
#include <CommonBase/ThreadTool.h>
#include <CommonBase/ThreadingMsgQueue.h>
#include <CommonBase/IConnection.h>
#include <CommonBase/BaseBuffer.h>
#include <CommonBase/TransmitData.h>
#include <CommonBase/netmsg.h>
#include <ServerBase/ServerSocket.h>
#include <CommonBase/AsyncQueue.h>
#include <CommonBase/TimerTask.h>
#include <textlog/textlog.h>
#include <MsgClientLib/MsgClient.h>

using namespace std;

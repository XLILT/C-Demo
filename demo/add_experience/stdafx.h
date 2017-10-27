// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#if defined(_MSC_VER)
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
#endif



// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�

#include <list>
#include <vector>

#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/thread.hpp>
#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <boost/timer.hpp>
#include <boost/lexical_cast.hpp>

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
#include <netmsg/rank_data_def.h>
#include <netmsg/netmsg_rank.h>
//#include <LogServerLib/data_def.h>
#include <Common/Tools.h>


#if defined(_MSC_VER)
#pragma comment(lib, "netmsg.lib")
#pragma comment(lib, "MsgClientLib.lib")
#pragma   comment(lib, "libmysql.lib")
#pragma   comment(lib, "CommonBase.lib")
#pragma   comment(lib, "TextLog.lib")
#pragma   comment(lib, "ServerBase.lib")
#pragma   comment(lib, "MySQLDB.lib")
#pragma   comment(lib, "Common.lib")
#endif


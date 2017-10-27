/*
 * =====================================================================================
 *
 *       Filename:  TransactDAO.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年12月17日 10时46分25秒
 *       Revision:  none
 *       Compiler:  clang++
 *
 *         Author:  wangfei (wangfei@douyu.tv)
 *		  Company:  武汉斗鱼网络科技有限公司
 *
 * =====================================================================================
 */
#include "stdafx.h"
#include "TransactDAO.h"

#include <MySqlDB/DBCommon.h>
#include <MySqlDB/MySqlZDB.h>
#include <MySqlDB/AdoHelper.h>
#include <MySqlDB/DBPool.h>

namespace dy
{
namespace complete_user_exp
{
    
TransactDAO::TransactDAO()
{
    memset(_url, 0, sizeof(_url));
    memset(_user, 0, sizeof(_user));
    memset(_passwd, 0, sizeof(_passwd));
    _db_pool = NULL;
}

bool TransactDAO::create(const char *url, const char *user, const char *passwd)
{
    if(NULL != url)
    {
        util::safe_strncpy(_url, url, sizeof(_url));
    }
    else
    {
        return false;
    }

    if(NULL != user)
    {
        util::safe_strncpy(_user, user, sizeof(_user));
    }
    else
    {
        return false;
    }

    if(NULL != passwd)
    {
        util::safe_strncpy(_passwd, passwd, sizeof(_passwd));
    }
    else
    {
        return false;
    }

    _db_pool =  new Stt::DB::SttDBPool(Stt::DB::dbt_MySQL, _url, _user, _passwd, 50);

    return true;
}

TransactDAO::~TransactDAO()
{
    delete _db_pool;
    _db_pool = NULL;
}

int TransactDAO::get_users_silver_info(unsigned int start_time, unsigned int end_time,
        UidSilverMap &map)
{
    int result = 0;
    char err[1024] = {0};
    char sql[1024] = {0};
    Stt::DB::MySQLConnection *conn = (Stt::DB::MySQLConnection *)_db_pool->GetConn();

    do
    {
        sprintf(sql, "Use stt_user");
        Stt::DB::MySQLCommand *cmd1 = (Stt::DB::MySQLCommand *)conn->CreateCommand();
        cmd1->ExecuteNoQuery(sql);
        delete cmd1;

        sprintf(sql, "select src_uid, silver from member_transaction_journal where type "
                "= 5 and dateline >= %u and dateline <= %u;", start_time, end_time);
        Stt::DB::MySQLCommand *cmd2 = (Stt::DB::MySQLCommand *)conn->CreateCommand(sql);
        if(NULL == cmd2)
        {
            result = conn->GetLastError();
            conn->GetLastErrorMessage(err, 1024);
            TL_FAST_LOG("./log/mysql_error.log", tlstDay, "create command error,"
                    "ret:%d err:%s", result, err);
            break;
        }

        Stt::DB::MySQLRecordset rs;
        if(NULL == cmd2->ExecuteQuery(rs))
        {
            result = conn->GetLastError();
            conn->GetLastErrorMessage(err, 1024);
            TL_FAST_LOG("./log/mysql_error.log", tlstDay, "ret:%d err:%s", result, err);
            break;
        }

        int uid = 0;
        int silver_diff = 0;
        while(rs.MoveNext())
        {
            // 数据库中的silver为正值
            uid = rs.AsUInt32("src_uid");
            silver_diff = rs.AsInt32("silver");
            UidSilverMap::iterator it = map.find(uid);
            if(it == map.end())
            {
                map[uid] = silver_diff;
            }
            else
            {
                map[uid] = it->second + silver_diff;
            }
        }
        delete cmd2;
    }while(0);

    _db_pool->CloseConn(conn);

    return result;
}

} // !namespace dy
} // !namespace complete_use_exp


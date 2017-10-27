/*
 * =====================================================================================
 *
 *       Filename:  YuChiTransactDAO.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年12月17日 10时46分40秒
 *       Revision:  none
 *       Compiler:  clang++
 *
 *         Author:  wangfei (wangfei@douyu.tv)
 *		  Company:  武汉斗鱼网络科技有限公司
 *
 * =====================================================================================
 */
#include "stdafx.h"
#include "YuChiTransactDAO.h"
#include <stdlib.h>

#include <MySqlDB/DBCommon.h>
#include <MySqlDB/MySqlZDB.h>
#include <MySqlDB/AdoHelper.h>
#include <MySqlDB/DBPool.h>

namespace dy
{
namespace complete_user_exp
{

YuChiTransactDAO::YuChiTransactDAO()
{
    _db_pool = NULL;
}

bool YuChiTransactDAO::create(const char *url, const char *user, const char *passwd)
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

YuChiTransactDAO::~YuChiTransactDAO()
{
}

int YuChiTransactDAO::get_users_gold_info(unsigned int start_time, unsigned int end_time,
        UidGoldMap &map)
{
    int result = 0;
    char err[1024] = {0};
    char sql[1024] = {0};
    Stt::DB::MySQLConnection *conn = (Stt::DB::MySQLConnection *)_db_pool->GetConn();

    do
    {
        sprintf(sql, "USE stt_chouqin");
        Stt::DB::MySQLCommand *cmd1 = (Stt::DB::MySQLCommand *)conn->CreateCommand();
        cmd1->ExecuteNoQuery(sql);
        delete cmd1;

        sprintf(sql, "select src_uid, gold_diff from chouqin_transaction_journal where "
                "(type = 2 or type = 9) and dateline >= %u and dateline <= %u;", 
                start_time, end_time);
        Stt::DB::MySQLCommand *cmd2 = (Stt::DB::MySQLCommand *)conn->CreateCommand(sql);
        if(cmd2 == NULL)
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

        unsigned int uid = 0;
        int gold_diff = 0;
        while(rs.MoveNext())
        {
            // 数据库中gold_diff为负值
            uid = rs.AsInt32("src_uid");
            gold_diff = rs.AsInt32("gold_diff");
            UidGoldMap::iterator it = map.find(uid);
            if(it == map.end())
            {
                map[uid] = 0 - gold_diff;
            }
            else
            {
                it->second = it->second - gold_diff;
            }
        }
        delete cmd2;

        sprintf(sql, "select des_uid, gold_diff from chouqin_transaction_journal where "
                "(type = 6 or type = 7) and dateline >= %u and dateline <= %u;", 
                start_time, end_time);
        Stt::DB::MySQLCommand *cmd3 = (Stt::DB::MySQLCommand *)conn->CreateCommand(sql);
        if(cmd3 == NULL)
        {
            result = conn->GetLastError();
            conn->GetLastErrorMessage(err, 1024);
            TL_FAST_LOG("./log/mysql_error.log", tlstDay, "create command error,"
                    "ret:%d err:%s", result, err);
            break;
        }

        Stt::DB::MySQLRecordset rs2;
        if(NULL == cmd3->ExecuteQuery(rs2))
        {
            result = conn->GetLastError();
            conn->GetLastErrorMessage(err, 1024);
            TL_FAST_LOG("./log/mysql_error.log", tlstDay, "ret:%d err:%s", result, err);
            break;
        }

        while(rs2.MoveNext())
        {
            // 数据库中gold_diff为负值
            uid = rs2.AsUInt32("des_uid");
            gold_diff = rs2.AsInt32("gold_diff");
            UidGoldMap::iterator it = map.find(uid);
            if(it == map.end())
            {
                map[uid] = 0 - gold_diff;
            }
            else
            {
                it->second = it->second - gold_diff;
            }
        }
        delete cmd3;
    }while(0);

    _db_pool->CloseConn(conn);

    return result;
}

} // !namespace dy
} // !namespace complete_user_exp

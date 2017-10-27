/*
 * =====================================================================================
 *
 *       Filename:  TitleDAO.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年12月17日 10时46分03秒
 *       Revision:  none
 *       Compiler:  clang++
 *
 *         Author:  wangfei (wangfei@douyu.tv)
 *		  Company:  武汉斗鱼网络科技有限公司
 *
 * =====================================================================================
 */
#include "stdafx.h"
#include "TitleDAO.h"
#include <stdlib.h>
#include <time.h>

#include <MySqlDB/DBCommon.h>
#include <MySqlDB/MySqlZDB.h>
#include <MySqlDB/AdoHelper.h>
#include <MySqlDB/DBPool.h>

namespace dy
{
namespace complete_user_exp
{

TitleDAO::TitleDAO()
{
    _db_pool = NULL;
}

bool TitleDAO::create(const char *url, const char *user, const char *passwd)
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

TitleDAO::~TitleDAO()
{
    if(NULL != _db_pool)
    {
        delete _db_pool;
    }
}

int TitleDAO::get_experience_change_info(unsigned int start_time, unsigned int end_time,
        UidExperienceMap &map)
{
    int result = 0;
    char err[1024] = {0};
    char sql[1024] = {0};
    Stt::DB::MySQLConnection *conn = (Stt::DB::MySQLConnection *)_db_pool->GetConn();

    do
    {
        sprintf(sql, "USE stt_title");
        Stt::DB::MySQLCommand *cmd1 = (Stt::DB::MySQLCommand *)conn->CreateCommand();
        cmd1->ExecuteNoQuery(sql);
        delete cmd1;

        sprintf(sql, "select uid, exp_diff from member_experience_detail where dateline >= %u"
                " and dateline <= %u;", start_time, end_time);
        Stt::DB::MySQLCommand * cmd2 = (Stt::DB::MySQLCommand *)conn->CreateCommand(sql);
        if(cmd2 == NULL)
        {
            result = conn->GetLastError();
            conn->GetLastErrorMessage(err, 1024);
            TL_FAST_LOG("./log/mysql_error.log", tlstDay, "create command error,"
                    " ret:%d err:%s", result, err);
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
        unsigned long exp_diff = 0;
        while(rs.MoveNext())
        {
            // 已经计算过的经验在补全过程中要扣除
            uid = rs.AsUInt32("uid");
            exp_diff = rs.AsUInt64("exp_diff");
            UidExperienceMap::iterator it =  map.find(uid);
            if(it == map.end())
            {
                map[uid] = exp_diff;
            }
            else
            {
                map[uid]= it->second + exp_diff;
            }
        }
    }while(0);

    _db_pool->CloseConn(conn);

    return result;
}

int TitleDAO::complete_user_experience(unsigned int uid, unsigned long exp, unsigned int time)
{
    int result = 0;
    char err[1024] = {0};
    char sql[1024] = {0};
    Stt::DB::MySQLConnection *conn = (Stt::DB::MySQLConnection *)_db_pool->GetConn();

    do
    {
        sprintf(sql, "USE stt_title");
        Stt::DB::MySQLCommand *cmd1 = (Stt::DB::MySQLCommand *)conn->CreateCommand();
        cmd1->ExecuteNoQuery(sql);
        delete cmd1;

        // 开启事务
        if(0 != conn->BeginTrans())
        {
            result = conn->GetLastError();
            conn->GetLastErrorMessage(err, 1024);
            TL_FAST_LOG("./log/mysql_error.log", tlstDay, "ret:%d err:%s", result, err);
            break;
        }

        // 更新summary表中记录
        sprintf(sql, "insert into member_experience_summary values(%u, %lu, 0, 0, 0, 0) "
                "on duplicate key update exp1 = exp1 + %lu;", uid, exp, exp);
        Stt::DB::MySQLCommand * cmd2 = (Stt::DB::MySQLCommand *)conn->CreateCommand(sql);
        if(cmd2 == NULL)
        {
            result = conn->GetLastError();
            conn->GetLastErrorMessage(err, 1024);
            TL_FAST_LOG("./log/mysql_error.log", tlstDay, "create command which update "
                    "stt_title.member_experience_summary error, ret:%d err:%s", result, err);
            break;
        }

        if(cmd2->ExecuteNoQuery() < 0)
        {
            result = conn->GetLastError();
            conn->GetLastErrorMessage(err, 1024);
            TL_FAST_LOG("./log/mysql_error.log", tlstDay, "execute command which update "
                    "stt_title.member_experience_summary error, ret:%d err:%s", result, err);
            break;
        }

        // 向detail表中插入补充记录
        sprintf(sql, "insert into member_experience_detail(uid, exp_type, change_type, "
            "exp_diff, room_id, dateline) values(%u, %u, %u, %lu, %u, %u);", uid, 0, 1,
            exp, 0, time);
        Stt::DB::MySQLCommand *cmd3 = (Stt::DB::MySQLCommand *)conn->CreateCommand(sql);
        if(cmd3 == NULL)
        {
            result = conn->GetLastError();
            conn->GetLastErrorMessage(err, 1024);
            TL_FAST_LOG("./log/mysql_error.log", tlstDay, "create command which insert into "
                    "stt_title.member_experience_detail error, ret:%d err:%s", result, err);
            break;
        }

        if(cmd3->ExecuteNoQuery() < 0)
        {
            result = conn->GetLastError();
            conn->GetLastErrorMessage(err, 1024);
            TL_FAST_LOG("./log/mysql_error.log", tlstDay, "execute command which insert into "
                    "stt_title.member_experience_detail error, ret:%d err:%s", result, err);
            break;
        }

        // 提交事务
        if(0 == result)
        {
            if(!conn->CommitTrans())
            {
                result = conn->GetLastError();
                conn->GetLastErrorMessage(err, 1024);
                TL_FAST_LOG("./log/mysql_error.log", tlstDay, "commit transaction error, ret:%d"
                        " err:%s", result, err);
            }
        }
        else
        {
            if(!conn->RollbackTrans())
            {
                result = conn->GetLastError();
                conn->GetLastErrorMessage(err, 1024);
                TL_FAST_LOG("./log/mysql_error.log", tlstDay, "Rollback error, ret:%d err:%s",
                        result, err);
            }
        }
    }while(0);

    _db_pool->CloseConn(conn);

    return result;
}

} // !namespace dy
} // !namespace complete_user_exp

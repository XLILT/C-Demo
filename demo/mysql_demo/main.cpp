#include "stdafx.h"
#include <MySqlDB/DBCommon.h>
#include <MySqlDB/MySqlZDB.h>
#include <MySqlDB/AdoHelper.h>
#include <MySqlDB/DBPool.h>
//#include <ServerBase/ServerBaseDAO.h>
#include <Common/DistServerDAO.h>

using namespace std;
using namespace Stt::DB;

class RoomMasterDAO :
    public SttServerBaseDAO
{
public:
    RoomMasterDAO(void) {}
    virtual ~RoomMasterDAO(void) {}

    void test_sql();
    void test_get_conns();
    int get_grap_blacklist_flag(char* blacklist_flag, int length);
};

void RoomMasterDAO::test_sql()
{
    int rid = 0, user_num = 0;
    char sql[] = {0}, err[1024] = {0};
    //IConnection* pconn = m_DBPool->GetConnUseful();
    IConnection* pconn = m_DBPool->GetConn();

    do
    {
        if(NULL == pconn)   // 数据库连接失败
        {
            TL_FAST_LOG("./log/error.log", tlstDay, "RoomMasterDAO::update_room_history_max_user_num batch GetConnUseful() ret NULL");
            break;
        }



        for(int i = 0; i < 2; i++)
        {
            ICommand* cmd = pconn->CreateCommand((char *)"call stt_online.update_room_history_max_user_num(?, ?)");
            //ICommand* cmd = pconn->CreateCommand((char *)"select unix_timestamp() as user_num_in_db");
            if(NULL == cmd)
            {
                cout << endl << "CreateCommand get last errno:" << pconn->GetLastError() << endl;
                cout << endl << "CreateCommand get last err:" << pconn->GetLastErrorMessage() << endl;
                pconn->GetLastErrorMessage(err, sizeof(err));
                TL_FAST_LOG("./log/error.log", tlstDay, "RoomMasterDAO::update_room_history_max_user_num(%d, %d) create cmd error : [sql:%s], [errmsg:%s], [errcode:%u]",
                    rid, user_num, sql, err, pconn->GetLastError());
                break;
            }

            cmd->AppendParameter(i);
            cmd->AppendParameter(i * 10);

            MySQLRecordset rs;
            if (!cmd->ExecuteQuery(rs))
            {
                cout << "ExecuteQuery get last errno:" << pconn->GetLastError() << endl;
                cout << "ExecuteQuery get last err:" << pconn->GetLastErrorMessage() << endl;
                pconn->GetLastErrorMessage(err, sizeof(err));
                TL_FAST_LOG("./log/error.log", tlstDay, "RoomMasterDAO::update_room_history_max_user_num(%d, %d) exe query error : [sql:%s], [errmsg:%s], [errcode:%u]",
                    rid, user_num, sql, err, pconn->GetLastError());
                delete cmd;
                continue;
            }

            if (rs.MoveNext())  // 查询db中的结果
            {
                int user_num_in_db = rs.AsInt32("user_num_in_db");
                cout << "MoveNext :" << user_num_in_db << endl;
                TL_FAST_LOG("./log/info.log", tlstDay, "RoomMasterDAO::update_room_history_max_user_num(%d, %d) [user_num_in_db=%d]", rid, user_num, user_num_in_db);
            }
            else
            {
                cout << "MoveNext get last errno:" << pconn->GetLastError() << endl;
                cout << "MoveNext get last err:" << pconn->GetLastErrorMessage() << endl;
                pconn->GetLastErrorMessage(err, sizeof(err));
                TL_FAST_LOG("./log/error.log", tlstDay, "RoomMasterDAO::update_room_history_max_user_num(%d, %d) move next error : [sql:%s], [errmsg:%s], [errcode:%u]",
                    rid, user_num, sql, err, pconn->GetLastError());
                delete cmd;
                continue;
            }

            while(rs.MoveNext())
            {}


            delete cmd;
        }
    }while(0);

    // 释放资源
    m_DBPool->CloseConn(pconn);

}

int RoomMasterDAO::get_grap_blacklist_flag(char* blacklist_flag, int length)
{
    int result = ET_UNKNOWN;
    MySQLConnection* pConn = NULL;
    MySQLCommand* cmd = NULL;
    do
    {
        pConn = (MySQLConnection*)m_DBPool->GetConn();
        TChar sql[1024];
        snprintf(sql, 1024, "USE stt_bigdata");
        cmd = (MySQLCommand *)pConn->CreateCommand();
        if (cmd->ExecuteNoQuery(sql) < 0)
        {
            break ;
        }
        //delete cmd;
        //cmd = NULL;

        snprintf(sql, 1024, "select * from stt_bigdata.chest_black_users");
        cmd = (MySQLCommand*)pConn->CreateCommand(sql);
        if (!cmd)
        {
            break ;
        }

        MySQLRecordset rs;
        if (!cmd->ExecuteQuery(rs))
        {
            break ;
        }

        //delete cmd;
        //cmd = NULL;

        if (rs.MoveNext() == 0)
        { // 这里返回到是1和0,1表示有数据
            cout << "no data"<< endl;
            break ;
        }
        else
        {
            cout << "has data"<< endl;
        }

        int id = rs.AsInt32("id");
        //rs.AsString("update_time", blacklist_flag, length);
        if (strcmp(blacklist_flag, "") == 0)
        { // 获取到的更新时间为空
            break ;
        }

        cout << "id: " << id << endl;

        result = ERROR_OK;
    }while (false);

    delete cmd;
    m_DBPool->CloseConn(pConn);

    return result;
}

void RoomMasterDAO::test_get_conns()
{
    while(true)
    {
        IConnection* pconn = m_DBPool->GetConnUseful();
        if (pconn)
        {
            // 释放资源
            m_DBPool->CloseConn(pconn);
        }
    }
}

class GetSharkBabyInfoSQLParam : public SQLParam
{
public:
    GetSharkBabyInfoSQLParam(const char *db_name, const char *sql, int uid) :
    SQLParam(db_name, sql),
    _uid(uid)
    {};

    virtual void append_parameter(Stt::DB::ICommand *cmd) const
    {
        cmd->AppendParameter(_uid);
    };

    int _uid;
};

class UpdateSharkBabyInfoSQLParam : public SQLParam
{
public:
    UpdateSharkBabyInfoSQLParam(const char *db_name, const char *sql, int uid, int zhaocai_end_ts) :
    SQLParam(db_name, sql),
    _uid(uid),
    _zhaocai_end_ts(zhaocai_end_ts)
    {};

    virtual void append_parameter(Stt::DB::ICommand *cmd) const
    {
        cmd->AppendParameter(_zhaocai_end_ts);
        cmd->AppendParameter(_uid);
    };

    int _uid;
    int _zhaocai_end_ts;
};

class SharkBabyInfo : public SimpleInfo
{
public:
    SharkBabyInfo() : SimpleInfo()
    {
        zhaocai_shark_baby_end_ts = 0;
        xiangrui_shark_baby_end_ts = 0;
        zhizun_shark_baby_end_ts = 0;
    }

    virtual void fill_with_recordset(Stt::DB::IRecordset *rs)
    {
        zhaocai_shark_baby_end_ts = rs->AsUInt32("zhaocai_end_ts");
        xiangrui_shark_baby_end_ts = rs->AsUInt32("xiangrui_end_ts");
        zhizun_shark_baby_end_ts = rs->AsUInt32("zhizun_end_ts");
    }

    void show_self_info()
    {
        cout << zhaocai_shark_baby_end_ts << ", "
            << xiangrui_shark_baby_end_ts << ", "
            << zhizun_shark_baby_end_ts << endl;
    }

    unsigned int zhaocai_shark_baby_end_ts; // 招财鲨鱼宝宝的结束时间戳
    unsigned int xiangrui_shark_baby_end_ts;// 祥瑞鲨鱼宝宝的结束时间戳
    unsigned int zhizun_shark_baby_end_ts;  // 至尊鲨鱼宝宝的结束时间戳
};

int main(int argc, char **argv)
{
    /*
    RoomMasterDAO *dao = new RoomMasterDAO;

    dao->m_DBURL.CopyFrom("192.168.5.105:3306");
    dao->m_DBUser.CopyFrom("root");
    dao->m_DBPass.CopyFrom("qazwsx");
    dao->Create();

    //dao->test_sql();
    //dao->test_get_conns();
    char str[1024];
    dao->get_grap_blacklist_flag(str, 1024);
    */

    /*
    for(int i = 0; i < atoi(argv[1]); i++)
    {
        boost::thread(boost::bind(&RoomMasterDAO::test_get_conns, dao));
    }
    */

    SttString db_url("192.168.5.15:3306");
    SttString user("root");
    SttString pass("qwe123");

    DistServerDAO *dao = new DistServerDAO(db_url, user, pass);
    dao->Create();

    GetSharkBabyInfoSQLParam sql_param("stt_cultivation", "select zhaocai_end_ts, xiangrui_end_ts, zhizun_end_ts "
        "from stt_cultivation.user_shark_baby_info where uid = ?", 21235);

    SharkBabyInfo info;

    cout << "ret: " << dao->get_simple_info(&sql_param, &info) << endl;
    info.show_self_info();

    UpdateSharkBabyInfoSQLParam update_sql_param("stt_cultivation", "update stt_cultivation.user_shark_baby_info set "
        "zhaocai_end_ts = ? where uid = ?", 21235, 123456);

    cout << "update ret: " << dao->update_info(&update_sql_param) << endl;

    SQLParam get_all_sql_param("stt_cultivation", "select zhaocai_end_ts, xiangrui_end_ts, zhizun_end_ts "
        "from stt_cultivation.user_shark_baby_info");

    vector<SharkBabyInfo *> shark_baby_info_array;
    //map<SharkBabyInfo *> shark_baby_info_array;

    cout << "ret: " << dao->get_simple_info_array(&get_all_sql_param, &shark_baby_info_array) << endl;

    BOOST_FOREACH(SharkBabyInfo * skbaby_info, shark_baby_info_array)
    {
        skbaby_info->show_self_info();
    }

    getchar();

    delete dao;
    TL_SHUTDOWN();

    return 0;
}

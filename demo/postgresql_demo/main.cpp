#include "stdafx.h"
#include <libpq-fe.h>
#include <MySqlDB/DBPool.h>
#include <boost/lexical_cast.hpp>

using namespace Stt::DB;

#if 0

using namespace pqxx;

connection * get_conn()
{
    connection *conn = NULL;
    try
    {
        conn = new connection("hostaddr=192.168.31.32 port=5432 dbname=testdb user=postgres password=passwd connect_timeout=10");
    }
    catch(std::exception &e)
    {
        cout << "connection exception: " << e.what() << endl;
    }

    return conn;
}

void test_transaction(connection *conn)
{
    try
    {
        transaction<> trans(*conn, "DemoTransaction");
        result ret = trans.exec("select * from table1;");

        //cout << ret.columns() << endl;
        for(result::size_type i = 0; i < ret.size(); ++i)
        {
            cout << ret[i]["column1"] << endl;
        }
    }
    catch(std::exception &e)
    {
        cout << "transaction exception: " << e.what() << endl;
    }
}

void test_parameterized(connection *conn)
{
    try
    {
        transaction<> trans(*conn, "DemoTransaction");
        result ret = trans.parameterized("select $1::int + $2::int as f")(10)(20).exec();
        cout << ret.columns() << endl;
        cout << ret.column_name(0) << endl;
        cout << ret[0][0] << endl;
    }
    catch(std::exception &e)
    {
        cout << "parameterized exception: " << e.what() << endl;
    }
}

void test_prepare(connection *conn)
{
    try
    {
        conn->prepare("p1", "select $1::int - $2::int as sub");
        conn->prepare("p1", "select $1::int + $2::int as add");

        transaction<> trans(*conn, "DemoTransaction");
        result ret = trans.prepared("p1")(3)(1).exec();

        cout << ret.columns() << endl;
        cout << ret.column_name(0) << endl;
        cout << ret[0][0] << endl;

        trans.commit();

        transaction<> trans1(*conn, "DemoTransaction1");
        result ret1 = trans1.prepared("p1")(3)(1).exec();

        cout << ret1.columns() << endl;
        cout << ret1.column_name(0) << endl;
        cout << ret1[0][0] << endl;

        result ret2 = trans1.prepared("p1")(10)(5).exec();

        cout << ret2.columns() << endl;
        cout << ret2.column_name(0) << endl;
        cout << ret2[0][0] << endl;

        trans1.commit();

    }
    catch(std::exception &e)
    {
        cout << "prepare exception: " << e.what() << endl;
    }
}

#endif

static void exit_nicely(PGconn *conn)
{
    PQfinish(conn);
    exit(1);
}

void demo1(int argc, char **argv)
{
    const char *conninfo;
    PGconn *conn;
    PGresult *res;
    int nFields;
    int i, j;
    /*
    740
    Chapter 31. libpq - C Library
    * If the user supplies a parameter on the command line, use it as the
    * conninfo string; otherwise default to setting dbname=postgres and using
    * environment variables or defaults for all other connection parameters.
    */
    if (argc > 1)
        conninfo = argv[1];
    else
        //conninfo = "dbname = postgres";
        conninfo = "hostaddr=192.168.31.32 port=5432 dbname=testdb user=postgres password=passwd connect_timeout=10";
    /* Make a connection to the database */
    conn = PQconnectdb(conninfo);
    /* Check to see that the backend connection was successfully made */
    if (PQstatus(conn) != CONNECTION_OK)
    {
        fprintf(stderr, "Connection to database failed: %s",
        PQerrorMessage(conn));
        exit_nicely(conn);
    }

    /*
    * Our test case here involves using a cursor, for which we must be inside
    * a transaction block. We could do the whole thing with a single
    * PQexec() of "select * from pg_database", but that’s too trivial to make
    * a good example.
    */
    /* Start a transaction block */
    res = PQexec(conn, "BEGIN;");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }

    /*
    * Should PQclear PGresult whenever it is no longer needed to avoid memory
    * leaks
    */
    PQclear(res);
    /*
    * Fetch rows from pg_database, the system catalog of databases
    */
    res = PQexec(conn, "DECLARE myportal CURSOR FOR select * from table1;");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "DECLARE CURSOR failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }

    PQclear(res);
    res = PQexec(conn, "FETCH ALL in myportal;");
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "FETCH ALL failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }

    /* first, print out the attribute names */
    nFields = PQnfields(res);
    for (i = 0; i < nFields; i++)
        printf("%-15s", PQfname(res, i));

    printf("\n\n");
    /* next, print out the rows */
    for (i = 0; i < PQntuples(res); i++)
    {
        for (j = 0; j < nFields; j++)
            printf("%-15s", PQgetvalue(res, i, j));

        printf("\n");
    }

    PQclear(res);
    /* close the portal ... we don’t bother to check for errors ... */
    res = PQexec(conn, "CLOSE myportal;");
    PQclear(res);
    /* end the transaction */
    res = PQexec(conn, "END;");
    PQclear(res);
    /* close the connection to the database and cleanup */
    PQfinish(conn);
}

void demo2(int argc, char **argv)
{
    const char *conninfo;
    PGconn *conn;
    PGresult *res;
    PGnotify *notify;
    int nnotifies;
    /*
    * If the user supplies a parameter on the command line, use it as the
    * conninfo string; otherwise default to setting dbname=postgres and using
    * environment variables or defaults for all other connection parameters.
    */
    if (argc > 1)
        conninfo = argv[1];
    else
        conninfo = "hostaddr=192.168.31.32 port=5432 dbname=testdb user=postgres password=passwd connect_timeout=10";
    /* Make a connection to the database */
    conn = PQconnectdb(conninfo);
    /* Check to see that the backend connection was successfully made */
    if (PQstatus(conn) != CONNECTION_OK)
    {
        fprintf(stderr, "Connection to database failed: %s",
        PQerrorMessage(conn));
        exit_nicely(conn);
    }
    /*
    * Issue LISTEN command to enable notifications from the rule’s NOTIFY.
    */
    res = PQexec(conn, "LISTEN TBL2");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "LISTEN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }
    /*
    * should PQclear PGresult whenever it is no longer needed to avoid memory
    * leaks
    */
    PQclear(res);
    /* Quit after four notifies are received. */
    nnotifies = 0;
    while (nnotifies < 4)
    {
    /*
    * Sleep until something happens on the connection. We use select(2)
    * to wait for input, but you could also use poll() or similar
    * facilities.
    */
        int sock;
        fd_set input_mask;
        sock = PQsocket(conn);
        if (sock < 0)
            break; /* shouldn’t happen */
        FD_ZERO(&input_mask);
        FD_SET(sock, &input_mask);
        if (select(sock + 1, &input_mask, NULL, NULL, NULL) < 0)
        {
            fprintf(stderr, "select() failed: %s\n", strerror(errno));
            exit_nicely(conn);
        }
        /* Now check for input */
        PQconsumeInput(conn);
        while ((notify = PQnotifies(conn)) != NULL)
        {
            fprintf(stderr,
            "ASYNC NOTIFY of ’%s’ received from backend PID %d\n",
            notify->relname, notify->be_pid);
            PQfreemem(notify);
            nnotifies++;
        }
    }
    fprintf(stderr, "Done.\n");
    /* close the connection to the database and cleanup */
    PQfinish(conn);
}

void demo3_test_result_type(int argc, char **argv)
{
    const char *conninfo;
    PGconn *conn;
    PGresult *res;
    /*
    * If the user supplies a parameter on the command line, use it as the
    * conninfo string; otherwise default to setting dbname=postgres and using
    * environment variables or defaults for all other connection parameters.
    */
    if (argc > 1)
        conninfo = argv[1];
    else
        conninfo = "hostaddr=192.168.31.32 port=5432 dbname=testdb user=postgres password=passwd connect_timeout=10";
    /* Make a connection to the database */
    conn = PQconnectdb(conninfo);
    /* Check to see that the backend connection was successfully made */
    if (PQstatus(conn) != CONNECTION_OK)
    {
        fprintf(stderr, "Connection to database failed: %s",
        PQerrorMessage(conn));
        exit_nicely(conn);
    }

    res = PQexec(conn, "select * from table1;");
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "select command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }

    cout << "PQntuples: " << PQntuples(res) << endl;
    cout << "PQnfields: " << PQnfields(res) << endl;
    cout << "PQbinaryTuples: " << PQbinaryTuples(res) << endl;
    cout << "PQfname: " << PQfname(res, 0) << endl;
    cout << "PQfnumber: " << PQfnumber(res, "column1") << endl;
    cout << "PQftable: " << PQftable(res, 1) << endl;
    cout << "PQftablecol: " << PQftablecol(res, 1) << endl;
    cout << "PQfformat: " << PQfformat(res, 1) << endl;
    cout << "PQftype: " << PQftype(res, 1) << endl;
    cout << "PQfsize: " << PQfsize(res, 1) << endl;
    cout << "PQfmod: " << PQfmod(res, 1) << endl;
    cout << "PQcmdStatus: " << PQcmdStatus(res) << endl;
    cout << "PQoidStatus: " << PQoidStatus(res) << endl;
    cout << "PQoidValue: " << PQoidValue(res) << endl;
    cout << "PQcmdTuples: " << PQcmdTuples(res) << endl;
    cout << "PQgetvalue: " << PQgetvalue(res, 0, 0) << endl;
    cout << "PQgetlength: " << PQgetlength(res, 0, 0) << endl;
    cout << "PQgetisnull: " << PQgetisnull(res, 0, 0) << endl;
    cout << "PQnparams: " << PQnparams(res) << endl;
    cout << "PQparamtype: " << PQparamtype(res, 0) << endl;

    PQclear(res);
    printf("Done.\n");
    /* close the connection to the database and cleanup */
    PQfinish(conn);
}

#if 0
void demo3()
{
    SttDBPool *db_pool = new SttDBPool(dbt_PostgreSQL, "192.168.31.32:5432", "postgres", "passwd", 512);
    IConnection *conn = db_pool->GetConnUseful();
    if (!conn)
    {
        cout << "connect error" << endl;

        return;
    }

    getchar();

    conn->Close();
    delete conn;
    delete db_pool;
}
#endif

void demo_print_PQconninfoOption()
{
    const char *conninfo;
    PGconn *conn;

    /*
    * If the user supplies a parameter on the command line, use it as the
    * conninfo string; otherwise default to setting dbname=postgres and using
    * environment variables or defaults for all other connection parameters.
    */
    conninfo = "hostaddr=192.168.31.32 port=5432 dbname=testdb user=postgres password=passwd connect_timeout=10";

    /* Make a connection to the database */
    conn = PQconnectdb(conninfo);
    /* Check to see that the backend connection was successfully made */
    if (PQstatus(conn) != CONNECTION_OK)
    {
        fprintf(stderr, "Connection to database failed: %s",
        PQerrorMessage(conn));
        exit_nicely(conn);
    }

    /*
    PQconninfoOption * conn_option = PQconninfo(conn);
    if (conn_option)
    {
        printf("conn_option: %p\n", conn_option);
        printf("keyword:%s\n", conn_option->keyword);
        printf("envvar:%s\n", conn_option->envvar);
        printf("compiled:%s\n", conn_option->compiled);
        printf("val:%s\n", conn_option->val);
        printf("label:%s\n", conn_option->label);
        printf("dispchar:%s\n", conn_option->dispchar);
        printf("dispsize:%d\n", conn_option->dispsize);
    }
    */
}

void demo_prepare()
{
    const char *conninfo;
    PGconn *conn;

    /*
    * If the user supplies a parameter on the command line, use it as the
    * conninfo string; otherwise default to setting dbname=postgres and using
    * environment variables or defaults for all other connection parameters.
    */
    conninfo = "hostaddr=192.168.31.32 port=5432 dbname=testdb user=postgres password=passwd connect_timeout=10";

    /* Make a connection to the database */
    conn = PQconnectdb(conninfo);
    /* Check to see that the backend connection was successfully made */
    if (PQstatus(conn) != CONNECTION_OK)
    {
        fprintf(stderr, "Connection to database failed: %s",
        PQerrorMessage(conn));
        exit_nicely(conn);
    }

    PGresult *pg_ret = PQprepare(conn, "", "INSERT INTO table1(column1) VALUES($1);", 0, NULL);
    if (PQresultStatus(pg_ret) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "Failed to prepare: %s\n", PQerrorMessage(conn));
        exit_nicely(conn);
    }

    try
    {
        const char *param_value[] = {boost::lexical_cast<string>(4).c_str()};
        pg_ret = PQexecPrepared(conn, "", sizeof(param_value)/ sizeof(char *), param_value, NULL, NULL, 0);
        if (PQresultStatus(pg_ret) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "Failed to exec prepared: %s\n", PQerrorMessage(conn));
            exit_nicely(conn);
        }
    }
    catch(...)
    {
        cout << "lexical cast exception" << endl;
    }
}

void test_string_transform()
{
    std::string m_cmd_str;
    int i = 0;
    std::string original_str = std::string("INSERT INTO table1(column1) VALUES(?);");

    // replace ? with $1,$2...
    std::size_t last_pos = 0;
    std::size_t found = original_str.find_first_of("?");
    while(found != std::string::npos)
    {
        if (found > last_pos)
        {
            m_cmd_str += original_str.substr(last_pos, found - last_pos);

            char num[4] = {0};
            snprintf(num, sizeof(num), "%d", ++i);
            m_cmd_str += "$" + std::string(num);

            last_pos = found + 1;  // jump character '?'
        }

        found = original_str.find_first_of("?", found + 1);
    }

    m_cmd_str += original_str.substr(last_pos, original_str.size() - last_pos);

    cout << m_cmd_str << endl;
}

void demo_stt_ExecuteQueryNoSTMT()
{
    SttDBPool *db_pool = new SttDBPool(dbt_PostgreSQL, "192.168.31.32:5432", "postgres", "passwd", 512);
    IConnection *conn = db_pool->GetConnUseful();
    if (!conn)
    {
        cout << "connect error" << endl;

        return;
    }

    do
    {
        static_cast<PostgreSQLConnection *>(conn)->SetDB("testdb");
        ICommand *cmd = conn->CreateCommand();
        if (!cmd)
        {
            cout << "CreateCommand error" << endl;

            break;
        }

        PostgreSQLRecordset rs;
        cmd->ExecuteQueryNoSTMT("select * from table1;", rs);
        while(rs.MoveNext())
        {
            cout << rs.AsInt32("column1") << endl;;
        }

        delete cmd;
    }while(0);


    conn->Close();
    delete conn;
    delete db_pool;
}

void demo_stt_ExecuteNoQuery()
{
    SttDBPool *db_pool = new SttDBPool(dbt_PostgreSQL, "192.168.31.32:5432", "postgres", "passwd", 512);
    IConnection *conn = db_pool->GetConnUseful();
    if (!conn)
    {
        cout << "connect error" << endl;

        return;
    }

    do
    {
        static_cast<PostgreSQLConnection *>(conn)->SetDB("testdb");
        ICommand *cmd = conn->CreateCommand();
        if (!cmd)
        {
            cout << "CreateCommand error" << endl;

            break;
        }


        cout << cmd->ExecuteNoQuery("insert into table1(column1) values(5);") << endl;

        delete cmd;
    }while(0);


    conn->Close();
    delete conn;
    delete db_pool;
}

void demo_stt_ExecuteNoQuery1()
{
    SttDBPool *db_pool = new SttDBPool(dbt_PostgreSQL, "192.168.31.32:5432", "postgres", "passwd", 512);
    IConnection *conn = db_pool->GetConnUseful();
    if (!conn)
    {
        cout << "connect error" << endl;

        return;
    }

    do
    {
        static_cast<PostgreSQLConnection *>(conn)->SetDB("testdb");
        ICommand *cmd = conn->CreateCommand("insert into table1(column1) values(?);");
        if (!cmd)
        {
            cout << "CreateCommand error" << endl;

            break;
        }


        cout << cmd->ExecuteNoQuery() << endl;

        cmd->AppendParameter(6);

        cout << cmd->ExecuteNoQuery() << endl;

        delete cmd;
    }while(0);


    conn->Close();
    delete conn;
    delete db_pool;
}

void demo_stt_ExecuteNoQuery2()
{
    SttDBPool *db_pool = new SttDBPool(dbt_PostgreSQL, "192.168.31.32:5432", "postgres", "passwd", 512);
    IConnection *conn = db_pool->GetConnUseful();
    if (!conn)
    {
        cout << "connect error" << endl;

        return;
    }

    do
    {
        static_cast<PostgreSQLConnection *>(conn)->SetDB("testdb");
        ICommand *cmd = conn->CreateCommand();
        if (!cmd)
        {
            cout << "CreateCommand error" << endl;

            break;
        }

        cout << cmd->PrepareCommand("insert into table1(column1) values(?);") << endl;

        cout << cmd->ExecuteNoQuery() << endl;

        cmd->AppendParameter(7);

        cout << cmd->ExecuteNoQuery() << endl;

        delete cmd;
    }while(0);

    conn->Close();
    delete conn;
    delete db_pool;
}

void demo_stt_ExecuteNoQuery3()
{
    SttDBPool *db_pool = new SttDBPool(dbt_PostgreSQL, "192.168.31.32:5432", "postgres", "passwd", 512);
    IConnection *conn = db_pool->GetConnUseful();
    if (!conn)
    {
        cout << "connect error" << endl;

        return;
    }

    do
    {
        static_cast<PostgreSQLConnection *>(conn)->SetDB("testdb");
        ICommand *cmd = conn->CreateCommand();
        if (!cmd)
        {
            cout << "CreateCommand error" << endl;

            break;
        }

        cout << cmd->PrepareCommand("delete from table1 where column1 <= 2;") << endl;

        cout << cmd->ExecuteNoQuery() << endl;

        delete cmd;
    }while(0);

    conn->Close();
    delete conn;
    delete db_pool;
}

void demo_stt_ExecuteQuery1()
{
    SttDBPool *db_pool = new SttDBPool(dbt_PostgreSQL, "192.168.31.32:5432", "postgres", "passwd", 512);
    IConnection *conn = db_pool->GetConnUseful();
    if (!conn)
    {
        cout << "connect error" << endl;

        return;
    }

    do
    {
        static_cast<PostgreSQLConnection *>(conn)->SetDB("testdb");
        ICommand *cmd = conn->CreateCommand();
        if (!cmd)
        {
            cout << "CreateCommand error" << endl;

            break;
        }

        cout << cmd->PrepareCommand("select * from table1 where column1 >= 4;") << endl;

        PostgreSQLRecordset rs;
        cmd->ExecuteQuery(rs);
        while(rs.MoveNext())
        {
            cout << rs.AsInt32("column1") << endl;;
        }

        delete cmd;
    }while(0);

    conn->Close();
    delete conn;
    delete db_pool;
}

void demo_stt_ExecuteQuery2()
{
    SttDBPool *db_pool = new SttDBPool(dbt_PostgreSQL, "192.168.31.32:5432", "postgres", "passwd", 512);
    IConnection *conn = db_pool->GetConnUseful();
    if (!conn)
    {
        cout << "connect error" << endl;

        return;
    }

    do
    {
        static_cast<PostgreSQLConnection *>(conn)->SetDB("testdb");
        ICommand *cmd = conn->CreateCommand();
        if (!cmd)
        {
            cout << "CreateCommand error" << endl;

            break;
        }

        cout << cmd->PrepareCommand("select * from table1 where column1 >= ?;") << endl;

        PostgreSQLRecordset rs;
        cout << cmd->ExecuteQuery(rs) << endl;

        cmd->AppendParameter(6);
        cout << cmd->ExecuteQuery(rs) << endl;
        while(rs.MoveNext())
        {
            cout << rs.AsInt32("column1") << endl;;
        }

        delete cmd;
    }while(0);

    conn->Close();
    delete conn;
    delete db_pool;
}

int main(int argc, char **argv)
{
    //demo1(argc, argv);

    //demo3();

    //demo_print_PQconninfoOption();

    //demo_prepare();

    //test_string_transform();

    //demo_stt_ExecuteQueryNoSTMT();

    //demo_stt_ExecuteNoQuery();

    //demo_stt_ExecuteNoQuery1();

    //demo_stt_ExecuteNoQuery2();

    //demo_stt_ExecuteNoQuery3();

    //demo_stt_ExecuteQuery1();

    demo_stt_ExecuteQuery2();

    //demo3_test_result_type(argc, argv);

    TL_SHUTDOWN();

    return 0;
}

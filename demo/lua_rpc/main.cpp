#include "stdafx.h"
#include <MsgClientLib/MsgClient.h>

extern "C" {
    #include <lua.h>  
    #include <lualib.h>  
    #include <lauxlib.h> 
}

std::string stt_rpc_impl(MsgClient* msg_client, int server_id, const char *func_name, const char *param)
{
    MsgClient::RpcRequestInfo rpc_req;
    rpc_req._receiver_id = server_id;
    rpc_req._timeout_ms = 5000;
    rpc_req._func_name = func_name;
    rpc_req._parameters = param;
    rpc_req._rpc_global_id = "123";
    rpc_req._password = "123";
    rpc_req._version = 1;

    SttString stt_str;
    msg_client->call_remote_function(rpc_req, &stt_str);

    return stt_str.c_UTF8();
}

static int stt_rpc(lua_State *L)
{
    int argc = lua_gettop(L);
    if(argc != 5)
    {
        return 0;
    }

    unsigned long msg_client_prt = 0;
    msg_client_prt = lua_tointeger(L, 1);
    msg_client_prt += lua_tointeger(L, 2) << 32;
    MsgClient* msg_client = reinterpret_cast<MsgClient *>(msg_client_prt);
    int server_id = lua_tonumber(L, 3);
    const char *func_name = lua_tostring(L, 4);
    const char *param = lua_tostring(L, 5);   

    //cout << msg_client << " " << server_id << " " << func_name << " " << param << endl;
    const char *ret = stt_rpc_impl(msg_client, server_id, func_name, param).c_str();
    lua_pushstring(L, ret);
    //lua_pushstring(L, "str");

    return 1;
}

int main(int argc, char **argv)
{

    SttAsyncQueue* AsyncQueue = new SttAsyncQueue;
    SttTimerTask* timer = new SttTimerTask(*AsyncQueue);
    MsgClient* msg_client = new MsgClient(timer);

    char ip[64] = "10.1.51.9";

    int port = 11001;
    int id = 666666;
    int choice = 0;
    printf("********Welcome to STT RPC Call Center********\n");
    printf("please choose server ip port and id config\n");
    printf("***0.set manully***\n");
    printf("***1.default config 10.1.51.9 11001 666666***\n");
    printf("***2.default config 192.168.1.64 11001 666666***\n");
    printf("***3.default config 192.168.5.14 11001 666666***\n");
    printf("***4.default config 192.168.5.4 11001 666666***\n");
    printf("***5.default config 192.168.6.24 11001 666666***\n");

    scanf("%d", &choice);
    if (0 == choice)
    {
        printf("please input server ip port and server's id: ");
        scanf("%s%d%d", ip, &port, &id);
    }
    if (1 == choice)
    {

    }
    else if(2 == choice)
    {
        snprintf(ip, sizeof(ip), "%s", "192.168.1.64");
        port = 11001;
    }
    else if(3 == choice)
    {
        snprintf(ip, sizeof(ip), "%s", "192.168.5.14");
        port = 11001;
    }
    else if(4 == choice)
    {
        snprintf(ip, sizeof(ip), "%s", "192.168.5.4");
        port = 11001;
    }
    else if(5 == choice)
    {
        snprintf(ip, sizeof(ip), "%s", "192.168.6.24");
        port = 11001;
    }

    msg_client->SetServer(ip, port);
    msg_client->Login(id, "rpc_tester", "rpc_tester");
    msg_client->set_server_init_done();

    SttSleep(1000);

    lua_State *L = lua_open();

    luaL_openlibs(L);

    lua_register(L, "stt_rpc", stt_rpc);

    lua_createtable(L, 2, 0);
    unsigned long msg_client_ptr = reinterpret_cast<unsigned long>(msg_client);

    lua_pushnumber(L, 1);
    lua_pushnumber(L, msg_client_ptr & 0xFFFFFFFF);

    lua_settable(L, -3);

    lua_pushnumber(L, 2);
    lua_pushnumber(L, (msg_client_ptr >> 32) & 0xFFFFFFFF);
    
    lua_settable(L, -3);
    lua_setglobal(L, "args");

    luaL_dofile(L, "main.lua");

    lua_close(L);

    return 0;
}

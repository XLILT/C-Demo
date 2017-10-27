#include "stdafx.h"
#include <fstream>

extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

boost::atomics::atomic_uint32_t call_count(0);

void status()
{
    while(true)
    {
        cout << call_count << endl;
        call_count = 0;
        SttSleep(1000);
    }
}

int add(int x, int y)
{
    call_count++;
    return x + y;
}

int add_for_lua(lua_State *L)
{
    lua_pushnumber(L, add(lua_tonumber(L, 1), lua_tonumber(L, 2)));   

    return 1;
}

void test_local_call()
{
    while(true)
    {
        add(1, 1);
    }
}

void test_lua_call()
{
    lua_State *L = lua_open();
    luaL_openlibs(L);
 
    lua_register(L, "add", add_for_lua);

    
    ifstream ifs("add_loop.lua");
    std::string add_loop_str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>()); 
   
    luaL_dofile(L, "add_loop.lua");
    //luaL_dostring(L, add_loop_str.c_str());
        
    lua_close(L);

}

int main(int argc, char **argv)
{
    boost::thread(boost::bind(&status));

    //test_local_call();
    test_lua_call();

    return 0;
}

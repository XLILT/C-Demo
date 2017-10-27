#include "stdafx.h"

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>

#ifdef __cplusplus
}
#endif //__cplusplus

static bool is_stop = false;
//static bool is_start = false;

int increase(int x)
{
    return ++x;
}

void test1()
{
    uint64_t count = 0;

    while(true)
    {
        if (is_stop)
        {
            break;
        }

        count = increase(count);
    }

    std::cout << "test1 count: " << count << std::endl;
}

void test2(lua_State *L)
{
    uint64_t count = 0;

    while(true)
    {
        if (is_stop)
        {
            break;
        }

        lua_getglobal(L, "increase");
        lua_pushnumber(L, count);
        lua_pcall(L, 1, 1, 0);

        count = lua_tonumber(L, -1);
    }

    std::cout << "test2 count: " << count << std::endl;
}

void timer_stop(int seconds)
{
    uint64_t start = SttGetTickCount();
    while(true)
    {
        if (SttGetTickCount() >= start + seconds * 1000)
        {
            is_stop = true;
        }
    }
}

int main(int argc, char **argv)
{
    lua_State *L = NULL;
    //init lua
    L = lua_open();
    //load basic libraries
    luaL_openlibs(L);
    //run script
    luaL_dofile(L, "test.lua");

    //get lua function "readFile"
    //lua_getglobal(L, "increase");
    //push args to stack
    //lua_pushstring()
    //call lua function
    //lua_pcall(L, 0, 1, 0);

    //printf("function readFile in test.lua retrun%lu:%s", sizeof(unsigned char), lua_tostring(L, -1));
    //printf("function readFile in test.lua retrun:%d", lua_tointeger(L, -1));

    //clear lua


    boost::thread(boost::bind(&timer_stop, atoi(argv[1])));
    //test1();
    //test1();
    test2(L);

    lua_close(L);
    return 0;
}

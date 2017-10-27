/*************************************************************************
    > File Name: main.cpp
    > Author: mxl2
    > Mail: xiaolongicx@gmail.com
    > Created Time: Wed 26 Apr 2017 04:07:16 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;


extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

static int average(lua_State *L)
{
    int n = lua_gettop(L);
    if(n <= 0)
    {
        return 0;
    }

    double sum = 0;
    
    int i = 1;
    for(/**/; i <= n; i++)
    {
        if(!lua_isnumber(L, i))
        {
            lua_pushstring(L, "Incorrect argument to 'average'");
            lua_error(L);
        }

        sum += lua_tonumber(L, i);
    }

    lua_pushnumber(L, sum / n);
    lua_pushnumber(L, sum);

    return 2;
}

int main(int argc, const char **argv)
{
    lua_State *L = lua_open();
    luaL_openlibs(L);
 
    lua_register(L, "average", average);
    //luaL_dofile(L, "e15.lua");
    luaL_dostring(L, "print(\"123\")");

    lua_getglobal(L, "avg");
    cout << "avg is:" << lua_tointeger(L, -1) << endl;

    lua_pop(L, 1);
    lua_getglobal(L, "sum");
    cout << "sum is:" << lua_tointeger(L, -1) << endl;
    
    lua_close(L);

    return 0;
}


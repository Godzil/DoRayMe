/*
 *  DoRayMe - a quick and dirty Raytracer
 *
 *  Main app
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <stdio.h>
#include <string.h>
#include <math.h>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

static int l_sin (lua_State *L) {
    double d = luaL_checknumber(L, 1);  /* get argument */
    lua_pushnumber(L, sin(d));  /* push result */
    return 1;  /* number of results */
}
#if 0
int main(int argc, char *argv[])
{
    char buff[256];
    int error;
    lua_State *L = luaL_newstate();   /* opens Lua */
    luaL_openlibs(L);             /* opens the basic library */

    lua_pushcfunction(L, l_sin);
    lua_setglobal(L, "mysin");
    printf("[0]>");

    while (fgets(buff, sizeof(buff), stdin) != NULL)
    {
        error = luaL_loadstring(L, buff) || lua_pcall(L, 0, LUA_MULTRET, 0);

        if (error)
        {
            fprintf(stderr, "%s\n", lua_tostring(L, -1));
            lua_pop(L, 1);  /* pop error message from the stack */
        }
        printf("[%d]>", lua_gettop(L));
    }

    lua_close(L);
    return 0;
}
#endif
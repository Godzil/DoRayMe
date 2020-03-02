/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Lua based Pattern header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_LUAPATTERN_H
#define DORAYME_LUAPATTERN_H

#include <pattern.h>
#include <stdio.h>
#include <string.h>

#ifndef ENABLE_LUA_SUPPORT
#error Cannot use the Lua Pattern generator with no Lua support disabled!
#endif

extern "C" {
#include <lua.h>
}

class LuaPattern : public Pattern
{
private:
    lua_State *L;
    char funcName[50];

public:
    LuaPattern(Colour a, Colour b) : Pattern(a, b), L(nullptr) { };

    void setLua(lua_State *L) {
        this->L = L;
    };

    void setLuaFunctionName(const char *name) {
        strncpy(this->funcName, name, 50);
    }

    Colour patternAt(Tuple point)
    {
        int isnum;
        double r, g, b;

        lua_getglobal(this->L, this->funcName);
        lua_pushnumber(this->L, point.x);
        lua_pushnumber(this->L, point.y);
        lua_pushnumber(this->L, point.z);

        lua_createtable(L, 3, 0);
        lua_pushnumber(L, this->a.x);
        lua_setfield(L, -2, "r");
        lua_pushnumber(L, this->a.y);
        lua_setfield(L, -2, "g");
        lua_pushnumber(L, this->a.z);
        lua_setfield(L, -2, "b");

        lua_createtable(L, 3, 0);
        lua_pushnumber(L, this->b.x);
        lua_setfield(L, -2, "r");
        lua_pushnumber(L, this->b.y);
        lua_setfield(L, -2, "g");
        lua_pushnumber(L, this->b.z);
        lua_setfield(L, -2, "b");

        if (lua_pcall(this->L, 5, 3, 0) != LUA_OK)
        {
            printf("Error running the Lua function '%s': %s\n", this->funcName,
                    lua_tostring(this->L, -1));
            return Colour(0, 0, 0);
        }

        r = lua_tonumberx(this->L, -3, &isnum);
        if (!isnum)
        {
            printf("Error: function '%s' must return numbers\n", this->funcName);
            lua_pop(this->L, 1);
            return Colour(0, 0, 0);
        }
        g = lua_tonumberx(this->L, -2, &isnum);
        if (!isnum)
        {
            printf("Error: function '%s' must return numbers\n", this->funcName);
            lua_pop(this->L, 1);
            return Colour(0, 0, 0);
        }
        b = lua_tonumberx(this->L, -1, &isnum);
        if (!isnum)
        {
            printf("Error: function '%s' must return numbers\n", this->funcName);
            lua_pop(this->L, 1);
            return Colour(0, 0, 0);
        }

        lua_pop(this->L, 1);
        return Colour(r, g, b);
    }

    void dumpMe(FILE *fp) {
        fprintf(fp, "\"Type\": \"Lua\",\n");
        Pattern::dumpMe(fp);
    }

};

#endif /* DORAYME_LUAPATTERN_H */

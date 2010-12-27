#ifndef LUA_H
 #define LUA_H

#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>
#include <lua5.1/lualib.h>

void init_lua ();
lua_State** state ();
void dbg (lua_State* L);

#endif



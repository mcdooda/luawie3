#ifndef LUAWIE_H
 #define LUAWIE_H

#include <lua5.1/lua.h>

int luaopen_luawie (lua_State* L);

int l_luawie_init        (lua_State* L);
int l_luawie_sleep       (lua_State* L);
int l_luawie_clear       (lua_State* L);
int l_luawie_stop        (lua_State* L);
int l_luawie_num_devices (lua_State* L);
int l_luawie_poll        (lua_State* L);

#endif



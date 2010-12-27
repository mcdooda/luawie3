#ifndef KEYBOARD_H
 #define KEYBOARD_H

#include <lua5.1/lua.h>

int luaopen_keyboard (lua_State* L);

int l_keyboard_set_state (lua_State* L);

#endif



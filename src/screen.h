#ifndef SCREEN_H
 #define SCREEN_H

#include <lua5.1/lua.h>

int luaopen_screen (lua_State* L);

int l_screen_width  (lua_State* L);
int l_screen_height (lua_State* L);

#endif

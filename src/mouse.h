#ifndef MOUSE_H
 #define MOUSE_H

#include <lua5.1/lua.h>

int luaopen_mouse (lua_State* L);

int l_mouse_cursor_set_position (lua_State* L);
int l_mouse_cursor_move         (lua_State* L);
int l_mouse_button_click        (lua_State* L);

#define MS_LEFT      1
#define MS_MIDDLE    2
#define MS_RIGHT     3
#define MS_WHEELUP   4
#define MS_WHEELDOWN 5

#endif



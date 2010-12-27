#include "mouse.h"
#include "newlib.h"
#include "primitives.h"
#include "lua.h"

int luaopen_mouse(lua_State* L)
{
	static const struct Function cursor[] = {
		{"set_position", l_mouse_cursor_set_position},
		{"move",         l_mouse_cursor_move},
		{NULL, NULL}
	};
	
	static const struct Function button[] = {
		{"click", l_mouse_button_click},
		{NULL, NULL}
	};
	
	static const struct Lib lib[] = {
		{"cursor", cursor},
		{"button", button},
		{NULL, NULL}
	};
	
	new_lib(L, "Mouse", lib, NULL);

	static const struct Constant MS[] = {
		{"LEFT",      MS_LEFT},
		{"MIDDLE",    MS_MIDDLE},
		{"RIGHT",     MS_RIGHT},
		{"WHEELUP",   MS_WHEELUP},
		{"WHEELDOWN", MS_WHEELDOWN},
		{NULL, 0}
	};
	
	new_constants(L, "MS", MS);
	
	return 0;
}

int l_mouse_cursor_set_position(lua_State* L)
{
	int x = luaL_checkint(L, 1);
	int y = luaL_checkint(L, 2);
	mouse_set_cursor_position(x, y);
	return 0;
}

int l_mouse_cursor_move(lua_State* L)
{
	int x = luaL_checkint(L, 1);
	int y = luaL_checkint(L, 2);
	mouse_move_cursor(x, y);
	return 0;
}

int l_mouse_button_click(lua_State* L)
{
	int button = luaL_checkint(L, 1);
	int state = lua_toboolean(L, 2);
	mouse_click(button, state);
	return 0;
}



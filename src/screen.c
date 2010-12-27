#include "screen.h"
#include "newlib.h"
#include "primitives.h"

int luaopen_screen(lua_State* L)
{
	static struct Function functions[] = {
		{"width",  l_screen_width},
		{"height", l_screen_height},
		{NULL, NULL}
	};
	
	new_lib(L, "Screen", NULL, functions);
	
	return 0;
}

int l_screen_width(lua_State* L)
{
	lua_pushnumber(L, screen_width());
	return 1;
}

int l_screen_height(lua_State* L)
{
	lua_pushnumber(L, screen_height());
	return 1;
}



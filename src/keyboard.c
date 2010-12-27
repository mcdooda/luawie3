#include "keyboard.h"
#include "newlib.h"
#include "primitives.h"
#include "lua.h"

int luaopen_keyboard(lua_State* L)
{
	static const struct Function functions[] = {
		{"set_state", l_keyboard_set_state},
		{NULL, NULL}
	};
	
	new_lib(L, "Keyboard", NULL, functions);
	
	return 0;
}

int l_keyboard_set_state(lua_State* L)
{
	const char* key = luaL_checkstring(L, 1);
	int state = lua_toboolean(L, 2);
	keyboard_set_state(key, state);
	return 0;
}

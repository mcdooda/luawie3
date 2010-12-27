#include <stdlib.h>
#include "lua.h"
#include "luawie.h"
#include "wiimote.h"
#include "nunchuk.h"
#include "classic.h"
#include "guitar.h"
#include "mouse.h"
#include "keyboard.h"
#include "screen.h"

void init_lua()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	
	luaopen_luawie(L);
	luaopen_wiimote(L);
	luaopen_nunchuk(L);
	luaopen_classic(L);
	luaopen_guitar(L);
	luaopen_mouse(L);
	luaopen_keyboard(L);
	luaopen_screen(L);
	
	static const char* api[] = {
		"api/wiimote.lua",
		"api/nunchuk.lua",
		"api/classic.lua",
		"api/guitar.lua",
		"api/keyboard.lua",
		"api/mouse.lua",
		"api/piestyle.lua",
		"api/multiplayer.lua",
		NULL
	};
	
	int i;
	for (i = 0; api[i] != NULL; i++)
	{
		int errcode = luaL_dofile(L, api[i]);
		if (errcode != 0)
		{
			printf("Error: %s %s\n", api[i], lua_tostring(L, -1));
			exit(1);
		}
	}
	
	*state() = L;
}

lua_State** state()
{
	static lua_State* L;
	return &L;
}

void dbg(lua_State* L)
{
	int top = lua_gettop(L);
	printf("top = %d\n", top);
	int i;
	for (i = 1; i <= top; i++)
	{
		printf("%d : %s (%s)\n", i, lua_tostring(L, i), lua_typename(L, lua_type(L, i)));
	}
}




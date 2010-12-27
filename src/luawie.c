#include "luawie.h"
#include "lua.h"
#include "newlib.h"
#include "primitives.h"
#include "devices.h"
#include "runscript.h"
#include "pollmode.h"

int luaopen_luawie(lua_State* L)
{
	static const struct Function functions[] = {
		{"init",        l_luawie_init},
		{"sleep",       l_luawie_sleep},
		{"clear",       l_luawie_clear},
		{"stop",        l_luawie_stop},
		{"num_devices", l_luawie_num_devices},
		{"poll",        l_luawie_poll},
		{NULL, NULL}
	};
	
	new_lib(L, "Luawie", NULL, functions);
	
	static const struct Constant POLL[] = {
		{"AUTO",     POLL_AUTO},
		{"THREADED", POLL_THREADED},
		{"EXPLICIT", POLL_EXPLICIT},
		{NULL, 0}
	};
	
	new_constants(L, "POLL", POLL);
	
	return 0;
}

int l_luawie_init(lua_State* L)
{
	static int initialized = 0;
	lua_pushboolean(L, !initialized);
	initialized = 1;
	return 1;
}

int l_luawie_sleep(lua_State* L)
{
	sleep_ms(lua_tonumber(L, 1));
	return 0;
}

int l_luawie_clear(lua_State* L)
{
	clear();
	return 0;
}

int l_luawie_stop(lua_State* L)
{
	script_stop();
	return 0;
}

int l_luawie_num_devices(lua_State* L)
{
	lua_pushinteger(L, num_devices(-1));
	return 1;
}

int l_luawie_poll(lua_State* L)
{
	if (lua_isnone(L, 1))
	{
		devices_poll();
	}
	else
	{
		int mode = luaL_checkint(L, 1);
		int period = luaL_optint(L, 2, 0);
		poll_set_mode(mode, period);
	}
	return 0;
}


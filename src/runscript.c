#include <stdlib.h>
#include "runscript.h"
#include "primitives.h"
#include "lua.h"
#include "pollmode.h"

int keep_running;

void script_run(const char* filename)
{
	lua_State* L = *state();
	if (luaL_loadfile(L, filename) == LUA_ERRFILE)
	{
		printf("luaL_dofile error: %s\n", lua_tostring(L, -1));
		exit(1);
	}
	sleep_ms(2000);
	script_begin();
	while (script_running())
	{
		lua_pushvalue(L, -1);
		poll();
		lua_call(L, 0, 0);
	}
	clear();
}

void script_begin()
{
	keep_running = 1;
}

int script_running()
{
	return keep_running;
}

void script_stop()
{
	keep_running = 0;
}



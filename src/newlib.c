#include "newlib.h"
#include "lua.h"

void new_lib(lua_State* L, const char* name, const struct Lib libs[], const struct Function functions[])
{
	lua_createtable(L, 0, libs_size(libs) + functions_size(functions));
	if (libs != NULL)
	{
		int i;
		for (i = 0; libs[i].name != NULL; i++)
		{
			const struct Function* funcs = libs[i].functions;
			lua_createtable(L, 0, functions_size(funcs));
			int j;
			for (j = 0; funcs[j].name != NULL; j++)
			{
				lua_pushstring(L, funcs[j].name);
				lua_pushcfunction(L, funcs[j].function);
				lua_settable(L, -3);
			}
			lua_pushstring(L, libs[i].name);
			lua_pushvalue(L, -2);
			lua_settable(L, -4);
			lua_pop(L, 1);
		}
	}
	if (functions != NULL)
	{
		int i;
		for (i = 0; functions[i].name != NULL; i++)
		{
			lua_pushstring(L, functions[i].name);
			lua_pushcfunction(L, functions[i].function);
			lua_settable(L, -3);
		}
	}
	lua_setglobal(L, name);
}

void new_constants(lua_State* L, const char* name, const struct Constant constants[])
{
	lua_createtable(L, 0, constants_size(constants));
	int i;
	for (i = 0; constants[i].name != NULL; i++)
	{
		lua_pushstring(L, constants[i].name);
		lua_pushinteger(L, constants[i].value);
		lua_settable(L, -3);
	}
	lua_setglobal(L, name);
}

int functions_size(const struct Function functions[])
{
	if (functions == NULL)
		return 0;
		
	int i;
	for (i = 0; functions[i].name != NULL; i++);
	return i;
}

int libs_size(const struct Lib libs[])
{
	if (libs == NULL)
		return 0;
		
	int i;
	for (i = 0; libs[i].name != NULL; i++);
	return i;
}

int constants_size(const struct Constant constants[])
{
	if (constants == NULL)
		return 0;
		
	int i;
	for (i = 0; constants[i].name != NULL; i++);
	return i;
}



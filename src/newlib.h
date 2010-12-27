#ifndef NEWLIB_H
 #define NEWLIB_H

#include <lua5.1/lua.h>

struct Function
{
	const char* name;
	const lua_CFunction function;
};

struct Lib
{
	const char* name;
	const struct Function* functions;
};

struct Constant
{
	const char* name;
	const int value;
};

void new_lib       (lua_State* L, const char* name, const struct Lib libs[], const struct Function functions[]);
void new_constants (lua_State* L, const char* name, const struct Constant constants[]);

/* used to create lua tables with the exact required size */
int functions_size (const struct Function functions[]);
int libs_size      (const struct Lib libs[]);
int constants_size (const struct Constant constants[]);

#endif




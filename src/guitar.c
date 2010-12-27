#include <math.h>
#include "guitar.h"
#include "lua.h"
#include "newlib.h"
#include "devices.h"

int luaopen_guitar(lua_State* L)
{
	static const struct Function button[] = {
		{"pressed", l_guitar_button_pressed},
		{NULL, NULL}
	};
	
	static const struct Function joystick[] = {
		{"polar",     l_guitar_joystick_polar},
		{"cartesian", l_guitar_joystick_cartesian},
		{NULL, NULL}
	};
	
	static const struct Function shoulder[] = {
		{"whammy_bar", l_guitar_shoulder_whammy_bar},
		{NULL, NULL}
	};
	
	static const struct Lib lib[] = {
		{"button", button},
		{"joystick", joystick},
		{"shoulder", shoulder},
		{NULL, NULL}
	};
	
	new_lib(L, "Guitar", lib, NULL);
	
	static const struct Constant GH[] = {
		{"STRUMUP",   GH_STRUMUP},
		{"YELLOW",    GH_YELLOW},
		{"GREEN",     GH_GREEN},
		{"BLUE",      GH_BLUE},
		{"RED",       GH_RED},
		{"ORANGE",    GH_ORANGE},
		{"PLUS",      GH_PLUS},
		{"MINUS",     GH_MINUS},
		{"STRUMDOWN", GH_STRUMDOWN},
		{NULL, 0}
	};
	
	new_constants(L, "GH", GH);
	
	return 0;
}

/* button */
int l_guitar_button_pressed(lua_State* L)
{
	int top = lua_gettop(L);
	int pressed = 1;
	int i;
	struct guitar_hero_3_t* guitar = get_guitar();
	for (i = 1; i <= top && pressed; i++)
	{
		int type = lua_type(L, i);
		luaL_argcheck(L, type == LUA_TTABLE || type == LUA_TNUMBER, i, "must be a table or a number");
		if (type == LUA_TTABLE)
		{
			size_t size = lua_objlen(L, i);
			int j;
			for (j = 1; j <= size && pressed; j++)
			{
				lua_pushinteger(L, j);
				lua_gettable(L, -2);
				int button = lua_tointeger(L, -1);
				pressed = IS_PRESSED(guitar, button);
			}
		}
		else
		{
			int button = lua_tointeger(L, i);
			pressed = IS_PRESSED(guitar, button);
		}
	}
	lua_pushboolean(L, pressed);
	return 1;
}

/* joystick */
int l_guitar_joystick_polar(lua_State* L)
{
    struct guitar_hero_3_t* guitar = get_guitar();
    lua_pushnumber(L, guitar->js.mag);
    lua_pushnumber(L, guitar->js.ang);
	return 2;
}

int l_guitar_joystick_cartesian(lua_State* L)
{
	struct guitar_hero_3_t* guitar = get_guitar();
	float r = guitar->js.mag;
	if (r == 0)
	{
		lua_pushnumber(L, 0);
		lua_pushnumber(L, 0);
	}
	else
	{
		float theta = guitar->js.ang;
		float rad = (theta - 90) * M_PI / 180;
		lua_pushnumber(L, cos(rad) * r);
		lua_pushnumber(L, sin(rad) * r);
	}
	return 2;
}

/* whammy bar */
int l_guitar_shoulder_whammy_bar(lua_State* L)
{
	struct guitar_hero_3_t* guitar = get_guitar();
	lua_pushnumber(L, guitar->whammy_bar);
	return 1;
}



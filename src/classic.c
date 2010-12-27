#include <math.h>
#include "classic.h"
#include "newlib.h"
#include "lua.h"
#include "devices.h"

int luaopen_classic(lua_State* L)
{
	static const struct Function button[] = {
		{"pressed", l_classic_button_pressed},
		{NULL, NULL}
	};
	
	static const struct Function left_joystick[] = {
		{"polar",     l_classic_left_joystick_polar},
		{"cartesian", l_classic_left_joystick_cartesian},
		{NULL, NULL}
	};
	
	static const struct Function right_joystick[] = {
		{"polar",     l_classic_right_joystick_polar},
		{"cartesian", l_classic_right_joystick_cartesian},
		{NULL, NULL}
	};
	
	static const struct Function shoulder[] = {
		{"left",  l_classic_shoulder_left},
		{"right", l_classic_shoulder_right},
		{NULL, NULL}
	};
	
	static const struct Lib lib[] = {
		{"button",         button},
		{"left_joystick",  left_joystick},
		{"right_joystick", right_joystick},
		{"shoulder",       shoulder},
		{NULL, NULL}
	};
	
	new_lib(L, "Classic", lib, NULL);
	
	static const struct Constant CC[] = {
		{"UP",    CC_UP},
		{"LEFT",  CC_LEFT},
		{"ZR",    CC_ZR},
		{"X",     CC_X},
		{"A",     CC_A},
		{"Y",     CC_Y},
		{"B",     CC_B},
		{"ZL",    CC_ZL},
		{"R",     CC_R},
		{"PLUS",  CC_PLUS},
		{"HOME",  CC_HOME},
		{"MINUS", CC_MINUS},
		{"L",     CC_L},
		{"DOWN",  CC_DOWN},
		{"RIGHT", CC_RIGHT},
		{NULL, 0}
	};
	
	new_constants(L, "CC", CC);
	
	return 0;
}

/* button */
int l_classic_button_pressed(lua_State* L)
{
	int top = lua_gettop(L);
	int pressed = 1;
	int i;
	struct classic_ctrl_t* classic = get_classic();
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
				pressed = IS_PRESSED(classic, button);
			}
		}
		else
		{
			int button = lua_tointeger(L, i);
			pressed = IS_PRESSED(classic, button);
		}
	}
	lua_pushboolean(L, pressed);
	return 1;
}

/* left joystick */
int l_classic_left_joystick_polar(lua_State* L)
{
    struct classic_ctrl_t* classic = get_classic();
    lua_pushnumber(L, classic->ljs.mag);
    lua_pushnumber(L, classic->ljs.ang);
	return 2;
}

int l_classic_left_joystick_cartesian(lua_State* L)
{
	struct classic_ctrl_t* classic = get_classic();
	float r = classic->ljs.mag;
	if (r == 0)
	{
		lua_pushnumber(L, 0);
		lua_pushnumber(L, 0);
	}
	else
	{
		float theta = classic->ljs.ang;
		float rad = (theta - 90) * M_PI / 180;
		lua_pushnumber(L, cos(rad) * r);
		lua_pushnumber(L, sin(rad) * r);
	}
	return 2;
}

/* right joystick */
int l_classic_right_joystick_polar(lua_State* L)
{
    struct classic_ctrl_t* classic = get_classic();
    lua_pushnumber(L, classic->rjs.mag);
    lua_pushnumber(L, classic->rjs.ang);
	return 2;
}

int l_classic_right_joystick_cartesian(lua_State* L)
{
	struct classic_ctrl_t* classic = get_classic();
	float r = classic->rjs.mag;
	if (r == 0)
	{
		lua_pushnumber(L, 0);
		lua_pushnumber(L, 0);
	}
	else
	{
		float theta = classic->rjs.ang;
		float rad = (theta - 90) * M_PI / 180;
		lua_pushnumber(L, cos(rad) * r);
		lua_pushnumber(L, sin(rad) * r);
	}
	return 2;
}

/* shoulder */
int l_classic_shoulder_left(lua_State* L)
{
	struct classic_ctrl_t* classic = get_classic();
	lua_pushnumber(L, classic->l_shoulder);
	return 1;
}

int l_classic_shoulder_right(lua_State* L)
{
	struct classic_ctrl_t* classic = get_classic();
	lua_pushnumber(L, classic->r_shoulder);
	return 1;
}



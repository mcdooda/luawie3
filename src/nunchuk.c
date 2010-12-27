#include <math.h>
#include "wiiuse_v0.12/src/wiiuse.h"
#include "nunchuk.h"
#include "newlib.h"
#include "devices.h"
#include "lua.h"

int luaopen_nunchuk(lua_State* L)
{
	static const struct Function button[] = {
		{"pressed", l_nunchuk_button_pressed},
		{NULL, NULL}
	};
	
	static const struct Function accel[] = {
		{"orient", l_nunchuk_accel_orient},
		{"accel",  l_nunchuk_accel_accel},
		{"gforce", l_nunchuk_accel_gforce},
		{NULL, NULL}
	};
	
	static const struct Function joystick[] = {
		{"polar",     l_nunchuk_joystick_polar},
		{"cartesian", l_nunchuk_joystick_cartesian},
		{NULL, NULL}
	};
	
	static const struct Lib lib[] = {
		{"button",   button},
		{"accel",    accel},
		{"joystick", joystick},
		{NULL, NULL}
	};
	
	new_lib(L, "Nunchuk", lib, NULL);
	
	static const struct Constant NC[] = {
		{"Z", NC_Z},
		{"C", NC_C},
		{NULL, 0}
	};
	
	new_constants(L, "NC", NC);
	
	return 0;
}

/* button */
int l_nunchuk_button_pressed(lua_State* L)
{
	int top = lua_gettop(L);
	int pressed = 1;
	int i;
	struct nunchuk_t* nunchuk = get_nunchuk();
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
				pressed = IS_PRESSED(nunchuk, button);
			}
		}
		else
		{
			int button = lua_tointeger(L, i);
			pressed = IS_PRESSED(nunchuk, button);
		}
	}
	lua_pushboolean(L, pressed);
	return 1;
}

/* accel */
int l_nunchuk_accel_orient(lua_State* L)
{
	struct nunchuk_t* nunchuk = get_nunchuk();
	int smooth = lua_toboolean(L, 1);
	if (smooth)
	{
		lua_pushnumber(L, nunchuk->orient.a_roll);
		lua_pushnumber(L, nunchuk->orient.a_pitch);
	}
	else
	{
		lua_pushnumber(L, nunchuk->orient.roll);
		lua_pushnumber(L, nunchuk->orient.pitch);
	}
	lua_pushnumber(L, nunchuk->orient.yaw);
	return 3;
}

int l_nunchuk_accel_accel(lua_State* L)
{
	struct nunchuk_t* nunchuk = get_nunchuk();
	lua_pushnumber(L, nunchuk->accel.x);
	lua_pushnumber(L, nunchuk->accel.y);
	lua_pushnumber(L, nunchuk->accel.z);
	return 3;
}

int l_nunchuk_accel_gforce(lua_State* L)
{
	struct nunchuk_t* nunchuk = get_nunchuk();
	lua_pushnumber(L, nunchuk->gforce.x);
	lua_pushnumber(L, nunchuk->gforce.y);
	lua_pushnumber(L, nunchuk->gforce.z);
	return 3;
}

/* joystick */
int l_nunchuk_joystick_polar(lua_State* L)
{
    struct nunchuk_t* nunchuk = get_nunchuk();
    lua_pushnumber(L, nunchuk->js.mag);
    lua_pushnumber(L, nunchuk->js.ang);
    return 2;
}

int l_nunchuk_joystick_cartesian(lua_State* L)
{
	struct nunchuk_t* nunchuk = get_nunchuk();
	float r = nunchuk->js.mag;
	if (r == 0)
	{
		lua_pushnumber(L, 0);
		lua_pushnumber(L, 0);
	}
	else
	{
		float theta = nunchuk->js.ang;
		float rad = (theta - 90) * M_PI / 180;
		lua_pushnumber(L, cos(rad) * r);
		lua_pushnumber(L, sin(rad) * r);
	}
	return 2;
}



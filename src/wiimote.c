#include "wiiuse_v0.12/src/wiiuse.h"
#include "wiimote.h"
#include "newlib.h"
#include "devices.h"
#include "lua.h"

int luaopen_wiimote(lua_State* L)
{
	static const struct Function led[] = {
		{"on",  l_wiimote_led_on},
		{"off", l_wiimote_led_off},
		{NULL, NULL}
	};
	
	static const struct Function rumble[] = {
		{"on",  l_wiimote_rumble_on},
		{"off", l_wiimote_rumble_off},
		{NULL, NULL}
	};
	
	static const struct Function button[] = {
		{"pressed", l_wiimote_button_pressed},
		{NULL, NULL}
	};
	
	static const struct Function accel[] = {
		{"enable",  l_wiimote_accel_enable},
		{"disable", l_wiimote_accel_disable},
		{"orient",  l_wiimote_accel_orient},
		{"accel",   l_wiimote_accel_accel},
		{"gforce",  l_wiimote_accel_gforce},
		{NULL, NULL}
	};
	
	static const struct Function ir[] = {
		{"enable",  l_wiimote_ir_enable},
		{"disable", l_wiimote_ir_disable},
		{"dot",     l_wiimote_ir_dot},
		{"cursor",  l_wiimote_ir_cursor},
		{NULL, NULL}
	};
	
	static const struct Function expansion[] = {
		{"type", l_wiimote_expansion_type},
		{NULL, NULL}
	};
	
	static const struct Lib lib[] = {
		{"led",       led},
		{"rumble",    rumble},
		{"button",    button},
		{"accel",     accel},
		{"ir",        ir},
		{"expansion", expansion},
		{NULL, NULL}
	};
	
	static const struct Function functions[] = {
		{"select", l_wiimote_select},
		{NULL, NULL}
	};
	
	new_lib(L, "Wiimote", lib, functions);
	
	static const struct Constant WM[] = {
		{"TWO",   WM_TWO},
		{"ONE",   WM_ONE},
		{"B",     WM_B},
		{"A",     WM_A},
		{"MINUS", WM_MINUS},
		{"HOME",  WM_HOME},
		{"LEFT",  WM_LEFT},
		{"RIGHT", WM_RIGHT},
		{"DOWN",  WM_DOWN},
		{"UP",    WM_UP},
		{"PLUS",  WM_PLUS},
		{NULL, 0}
	};
	
	new_constants(L, "WM", WM);
	
	static const struct Constant EXP[] = {
		{"NC",  EXP_NC},
		{"CC",  EXP_CC},
		{"GH3", EXP_GH3},
		{NULL, 0}
	};
	
	new_constants(L, "EXP", EXP);
	
	return 0;	
}

/* led */
int l_wiimote_led_on(lua_State* L)
{
	struct wiimote_t* wiimote = get_wiimote();
	int leds = wiimote->leds;
	int led_codes[] = { WIIMOTE_LED_1, WIIMOTE_LED_2, WIIMOTE_LED_3, WIIMOTE_LED_4 };
	if (lua_type(L, 1) == LUA_TTABLE)
	{
		size_t size = lua_objlen(L, 1);
		int i;
		for (i = 1; i <= size; i++)
		{
			lua_pushinteger(L, i);
			lua_gettable(L, 1);
			int led = lua_tointeger(L, -1);
			luaL_argcheck(L, led >= 1 && led <= 4, 1, "values in arg #1 must be 1, 2, 3 or 4");
			leds |= led_codes[led - 1];
		}
	}
	else
	{
		int top = lua_gettop(L);
		int i;
		for (i = 1; i <= top; i++)
		{
			int led = lua_tointeger(L, i);
			luaL_argcheck(L, led >= 1 && led <= 4, 1, "must be 1, 2, 3 or 4");
			leds |= led_codes[led - 1];
		}
	}
	wiiuse_set_leds(wiimote, leds);
	return 0;
}

int l_wiimote_led_off(lua_State* L)
{
	struct wiimote_t* wiimote = get_wiimote();
	int leds = wiimote->leds;
	int led_codes[] = { WIIMOTE_LED_1, WIIMOTE_LED_2, WIIMOTE_LED_3, WIIMOTE_LED_4 };
	if (lua_type(L, 1) == LUA_TTABLE)
	{
		size_t size = lua_objlen(L, 1);
		int i;
		for (i = 1; i <= size; i++)
		{
			lua_pushinteger(L, i);
			lua_gettable(L, 1);
			int led = lua_tointeger(L, -1);
			luaL_argcheck(L, led >= 1 && led <= 4, 1, "must be 1, 2, 3 or 4");
			leds &= ~led_codes[led - 1];
		}
	}
	else
	{
		int top = lua_gettop(L);
		int i;
		for (i = 1; i <= top; i++)
		{
			int led = lua_tointeger(L, i);
			luaL_argcheck(L, led >= 1 && led <= 4, 1, "must be 1, 2, 3 or 4");
			leds &= ~led_codes[led - 1];
		}
	}
	wiiuse_set_leds(wiimote, leds);
	return 0;
}

/* rumble */
int l_wiimote_rumble_on(lua_State* L)
{
	wiiuse_rumble(get_wiimote(), 1);
	return 0;
}

int l_wiimote_rumble_off(lua_State* L)
{
	wiiuse_rumble(get_wiimote(), 0);
	return 0;
}

/* button */
int l_wiimote_button_pressed(lua_State* L)
{
	int top = lua_gettop(L);
	int pressed = 1;
	int i;
	struct wiimote_t* wiimote = get_wiimote();
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
				pressed = IS_PRESSED(wiimote, button);
			}
		}
		else
		{
			int button = lua_tointeger(L, i);
			pressed = IS_PRESSED(wiimote, button);
		}
	}
	lua_pushboolean(L, pressed);
	return 1;
}

/* accel */
int l_wiimote_accel_enable(lua_State* L)
{
	wiiuse_motion_sensing(get_wiimote(), 1);
	return 0;
}

int l_wiimote_accel_disable(lua_State* L)
{
	wiiuse_motion_sensing(get_wiimote(), 0);
	return 0;
}

int l_wiimote_accel_orient(lua_State* L)
{
	struct wiimote_t* wiimote = get_wiimote();
	int smooth = lua_toboolean(L, 1);
	if (smooth)
	{
		lua_pushnumber(L, wiimote->orient.a_roll);
		lua_pushnumber(L, wiimote->orient.a_pitch);
	}
	else
	{
		lua_pushnumber(L, wiimote->orient.roll);
		lua_pushnumber(L, wiimote->orient.pitch);
	}
	lua_pushnumber(L, wiimote->orient.yaw);
	return 3;
}

int l_wiimote_accel_accel(lua_State* L)
{
	struct wiimote_t* wiimote = get_wiimote();
	lua_pushnumber(L, wiimote->accel.x);
	lua_pushnumber(L, wiimote->accel.y);
	lua_pushnumber(L, wiimote->accel.z);
	return 3;
}

int l_wiimote_accel_gforce(lua_State* L)
{
	struct wiimote_t* wiimote = get_wiimote();
	lua_pushnumber(L, wiimote->gforce.x);
	lua_pushnumber(L, wiimote->gforce.y);
	lua_pushnumber(L, wiimote->gforce.z);
	return 3;
}

/* ir */
int l_wiimote_ir_enable(lua_State* L)
{
	wiiuse_set_ir(get_wiimote(), 1);
	return 0;
}

int l_wiimote_ir_disable(lua_State* L)
{
	wiiuse_set_ir(get_wiimote(), 0);
	return 0;
}

int l_wiimote_ir_dot(lua_State* L)
{
	int dot_id = luaL_checkint(L, 1);
	struct ir_dot_t dot = get_wiimote()->ir.dot[dot_id];
	lua_pushboolean(L, dot.visible);
	lua_pushnumber(L, dot.x);
	lua_pushnumber(L, dot.y);
	return 3;
}

int l_wiimote_ir_cursor(lua_State* L)
{
	struct wiimote_t* wiimote = get_wiimote();
	lua_pushnumber(L, wiimote->ir.x);
	lua_pushnumber(L, wiimote->ir.y);
	lua_pushnumber(L, wiimote->ir.z);
	return 3;
}

/* expansion */
int l_wiimote_expansion_type(lua_State* L)
{
	struct wiimote_t* wiimote = get_wiimote();
	lua_pushinteger(L, wiimote->exp.type);
	return 1;
}

/* functions */
int l_wiimote_select(lua_State* L)
{
	int device_id = lua_tointeger(L, 1);
	luaL_argcheck(L, device_id >= 1 && device_id <= 4, 1, "must be 1, 2, 3 or 4");
	current_wiimote_id(device_id - 1);
	return 0;
}



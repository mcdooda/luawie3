#ifndef NUNCHUK_H
 #define NUNCHUK_H

#include <lua5.1/lua.h>
#include "wiiuse_v0.12/src/wiiuse.h"

int luaopen_nunchuk (lua_State* L);

/* button */
int l_nunchuk_button_pressed (lua_State* L);

/* accel */
int l_nunchuk_accel_orient (lua_State* L);
int l_nunchuk_accel_accel  (lua_State* L);
int l_nunchuk_accel_gforce (lua_State* L);

/* joystick */
int l_nunchuk_joystick_polar     (lua_State* L);
int l_nunchuk_joystick_cartesian (lua_State* L);

/* buttons constants */
#define NC_Z NUNCHUK_BUTTON_Z
#define NC_C NUNCHUK_BUTTON_C

#endif



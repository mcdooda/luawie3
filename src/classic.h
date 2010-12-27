#ifndef CLASSIC_H
 #define CLASSIC_H

#include <lua5.1/lua.h>

int luaopen_classic (lua_State* L);

/* button */
int l_classic_button_pressed (lua_State* L);

/* left joystick */
int l_classic_left_joystick_polar     (lua_State* L);
int l_classic_left_joystick_cartesian (lua_State* L);

/* right joystick */
int l_classic_right_joystick_polar     (lua_State* L);
int l_classic_right_joystick_cartesian (lua_State* L);

/* shoulder */
int l_classic_shoulder_left  (lua_State* L);
int l_classic_shoulder_right (lua_State* L);

/* buttons constants */
#define CC_UP    CLASSIC_CTRL_BUTTON_UP
#define CC_LEFT  CLASSIC_CTRL_BUTTON_LEFT
#define CC_ZR    CLASSIC_CTRL_BUTTON_ZR
#define CC_X     CLASSIC_CTRL_BUTTON_X
#define CC_A     CLASSIC_CTRL_BUTTON_A
#define CC_Y     CLASSIC_CTRL_BUTTON_Y
#define CC_B     CLASSIC_CTRL_BUTTON_B
#define CC_ZL    CLASSIC_CTRL_BUTTON_ZL
#define CC_R     CLASSIC_CTRL_BUTTON_FULL_R
#define CC_PLUS  CLASSIC_CTRL_BUTTON_PLUS
#define CC_HOME  CLASSIC_CTRL_BUTTON_HOME
#define CC_MINUS CLASSIC_CTRL_BUTTON_MINUS
#define CC_L     CLASSIC_CTRL_BUTTON_FULL_L
#define CC_DOWN  CLASSIC_CTRL_BUTTON_DOWN
#define CC_RIGHT CLASSIC_CTRL_BUTTON_RIGHT

#endif



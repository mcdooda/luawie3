#ifndef WIIMOTE_H
 #define WIIMOTE_H

#include <lua5.1/lua.h>
#include "wiiuse_v0.12/src/wiiuse.h"

int luaopen_wiimote(lua_State* L);

/* led */
int l_wiimote_led_on  (lua_State* L);
int l_wiimote_led_off (lua_State* L);

/* rumble */
int l_wiimote_rumble_on  (lua_State* L);
int l_wiimote_rumble_off (lua_State* L);

/* button */
int l_wiimote_button_pressed (lua_State* L);

/* accel */
int l_wiimote_accel_enable  (lua_State* L);
int l_wiimote_accel_disable (lua_State* L);
int l_wiimote_accel_orient  (lua_State* L);
int l_wiimote_accel_accel   (lua_State* L);
int l_wiimote_accel_gforce  (lua_State* L);

/* ir */
int l_wiimote_ir_enable  (lua_State* L);
int l_wiimote_ir_disable (lua_State* L);
int l_wiimote_ir_dot     (lua_State* L);
int l_wiimote_ir_cursor  (lua_State* L);

/* expansion */
int l_wiimote_expansion_type (lua_State* L);

/* functions */
int l_wiimote_select (lua_State* L);

/* button constants */
#define WM_TWO   WIIMOTE_BUTTON_TWO
#define WM_ONE   WIIMOTE_BUTTON_ONE
#define WM_B     WIIMOTE_BUTTON_B
#define WM_A     WIIMOTE_BUTTON_A
#define WM_MINUS WIIMOTE_BUTTON_MINUS
#define WM_HOME  WIIMOTE_BUTTON_HOME
#define WM_LEFT  WIIMOTE_BUTTON_LEFT
#define WM_RIGHT WIIMOTE_BUTTON_RIGHT
#define WM_DOWN  WIIMOTE_BUTTON_DOWN
#define WM_UP    WIIMOTE_BUTTON_UP
#define WM_PLUS  WIIMOTE_BUTTON_PLUS

/* expansions type */
#define EXP_NC  EXP_NUNCHUK
#define EXP_CC  EXP_CLASSIC
#define EXP_GH3 EXP_GUITAR_HERO_3

#endif



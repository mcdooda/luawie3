#ifndef GUITAR_H
 #define GUITAR_H

#include <lua5.1/lua.h>

int luaopen_guitar (lua_State* L);

/* button */
int l_guitar_button_pressed (lua_State* L);

/* joystick */
int l_guitar_joystick_polar     (lua_State* L);
int l_guitar_joystick_cartesian (lua_State* L);

/* whammy bar */
int l_guitar_shoulder_whammy_bar (lua_State* L);

/* buttons constants */
#define GH_STRUMUP   GUITAR_HERO_3_BUTTON_STRUM_UP
#define GH_YELLOW    GUITAR_HERO_3_BUTTON_YELLOW
#define GH_GREEN     GUITAR_HERO_3_BUTTON_GREEN
#define GH_BLUE      GUITAR_HERO_3_BUTTON_BLUE
#define GH_RED       GUITAR_HERO_3_BUTTON_RED
#define GH_ORANGE    GUITAR_HERO_3_BUTTON_ORANGE
#define GH_PLUS      GUITAR_HERO_3_BUTTON_PLUS
#define GH_MINUS     GUITAR_HERO_3_BUTTON_MINUS
#define GH_STRUMDOWN GUITAR_HERO_3_BUTTON_STRUM_DOWN

#endif



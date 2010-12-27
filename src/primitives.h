#ifndef PRIMITIVES_H
 #define PRIMITIVES_H

/* misc */
void sleep_ms (int timeout_ms);
void clear ();

/* screen dimensions */
unsigned int screen_width ();
unsigned int screen_height ();

/* mouse */
void mouse_set_cursor_position (int x, int y);
void mouse_move_cursor         (int x, int y);
void mouse_click (int button, int state);

/* keyboard */
void keyboard_set_state (const char* key, int state);

#endif



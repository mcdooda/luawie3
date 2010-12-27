#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>
#include "primitives.h"

/* misc */
void sleep_ms(int timeout_ms)
{
	struct timeval tv;
	tv.tv_sec = timeout_ms / 1000;
	tv.tv_usec = (timeout_ms % 1000) * 1000;
	select(0, NULL, NULL, NULL, &tv);
}

void clear()
{
	system("clear");
}

/* screen dimensions */
unsigned int screen_width()
{
	static unsigned int width = 0;
	if (width == 0)
	{
		Display* display = XOpenDisplay(NULL);
		width = XDisplayWidth(display, XDefaultScreen(display));
		XCloseDisplay(display);
	}
	return width;
}

unsigned int screen_height()
{
	static unsigned int height = 0;
	if (height == 0)
	{
		Display* display = XOpenDisplay(NULL);
		height = XDisplayHeight(display, XDefaultScreen(display));
		XCloseDisplay(display);
	}
	return height;
}

/* mouse */
void mouse_set_cursor_position(int x, int y)
{
	Display* display = XOpenDisplay(NULL);
	XTestFakeMotionEvent(display, -1, x, y, 0);
	XCloseDisplay(display);
}

void mouse_move_cursor(int x, int y)
{
	Display* display = XOpenDisplay(NULL);
	XTestFakeRelativeMotionEvent(display, x, y, 0);
	XCloseDisplay(display);
}

void mouse_click(int button, int state)
{
	Display* display = XOpenDisplay(NULL);
	XTestFakeButtonEvent(display, button, state, 0);
	XCloseDisplay(display);
}

/* keyboard */
void keyboard_set_state (const char* key, int state)
{
	Display* display = XOpenDisplay(NULL);
	KeySym sym = XStringToKeysym(key);
	KeyCode keycode = XKeysymToKeycode(display, sym);
	XTestFakeKeyEvent(display, keycode, state, 0);
	XCloseDisplay(display);
}



#ifndef POLLMODE_H
 #define POLLMODE_H

void poll();

void poll_set_mode (int new_mode, int param);

void  poll_threaded_init (int period);
void* poll_threaded_fn   (void* param);
void  poll_threaded_quit ();

#define POLL_AUTO     1
#define POLL_THREADED 2
#define POLL_EXPLICIT 3
#define POLL_QUIT     4

#endif



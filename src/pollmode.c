#include <pthread.h>
#include "pollmode.h"
#include "devices.h"
#include "primitives.h"

int mode = POLL_AUTO;

struct
{
	pthread_t thread;
	int period;
} mode_threaded;

void poll()
{
	if (mode == POLL_AUTO)
		devices_poll();
}

void poll_set_mode(int new_mode, int param)
{
	if (mode == new_mode) return;
	int old_mode = mode;
	mode = new_mode;
	switch (old_mode)
	{
		case POLL_THREADED:
		poll_threaded_quit();
		break;
		
		default:;
	}
	switch (new_mode)
	{
		case POLL_THREADED:
		{
			int period = param;
			poll_threaded_init(period);
		}
		break;
		
		default:;
	}
}

void poll_threaded_init(int period)
{
	mode_threaded.period = period;
	pthread_create(&mode_threaded.thread, NULL, &poll_threaded_fn, NULL);
}

void* poll_threaded_fn(void* param)
{
	while (mode == POLL_THREADED)
	{
		devices_poll();
		sleep_ms(mode_threaded.period);
	}
	return NULL;
}

void poll_threaded_quit()
{
	pthread_join(mode_threaded.thread, NULL);
}



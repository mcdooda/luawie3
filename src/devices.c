#include <stdio.h>
#include <stdlib.h>
#include "devices.h"
#include "primitives.h"

void devices_connect(int num_wiimotes)
{
	struct wiimote_t** wiimotes = wiiuse_init(num_wiimotes);
	
	int found = 0;
	
	while (found < num_wiimotes)
	{
		found = wiiuse_find(wiimotes, num_wiimotes, 1);
		if (found == 0)
			sleep_ms(1000);
	}
	
	int connected = wiiuse_connect(wiimotes, num_wiimotes);
	
	if (connected >= num_wiimotes)
	{
		printf("%d wiimotes connected.\n", connected);
	}
	else
	{
		printf("Could not connect to %d wiimotes.\n", num_wiimotes);
		exit(1);
	}
	
	*get_devices() = wiimotes;
	num_devices(num_wiimotes);
}

void devices_disconnect()
{
	wiiuse_cleanup(*get_devices(), num_devices(-1));
}

void devices_poll()
{
	wiiuse_poll(*get_devices(), num_devices(-1));
}

int current_wiimote_id(int current)
{
	static int current_wiimote_id = 0;
	
	if (current >= 0)
		current_wiimote_id = current;
		
	return current_wiimote_id;
}

int num_devices(int num)
{
	static int num_devices = 0;
	
	if (num >= 0)
		num_devices = num;
		
	return num_devices;
}

struct wiimote_t*** get_devices()
{
	static struct wiimote_t** wiimotes;
	return &wiimotes;
}

struct wiimote_t* get_wiimote()
{
	return (*get_devices())[current_wiimote_id(-1)];
}

struct nunchuk_t* get_nunchuk()
{
	return (struct nunchuk_t*) &get_wiimote()->exp.nunchuk;
}

struct classic_ctrl_t* get_classic()
{
	return (struct classic_ctrl_t*) &get_wiimote()->exp.classic;
}

struct guitar_hero_3_t* get_guitar()
{
	return (struct guitar_hero_3_t*) &get_wiimote()->exp.gh3;
}


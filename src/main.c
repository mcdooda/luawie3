#include <stdio.h>
#include <stdlib.h>

#include "signals.h"
#include "lua.h"
#include "devices.h"
#include "runscript.h"

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Usage: %s <script.lua> [1-4]\n", argv[0]);
		exit(1);
	}
	
	char* script = argv[1];
	int num_wiimotes = 1;
	if (argc >= 3)
	{
		num_wiimotes = atoi(argv[2]);
		if (num_wiimotes < 1 || num_wiimotes > 4)
		{
			printf("Invalid number of wiimotes: %d\n", num_wiimotes);
			exit(1);
		}
	}
	
	init_signals();
	devices_connect(num_wiimotes);
	init_lua();
	script_run(script);
	devices_disconnect();
	return 0;
}



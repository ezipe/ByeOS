#include "shell.h"
#include <drivers/kbd.h>
#include <drivers/vga.h>
#include <drivers/power.h>
#include <common.h>

static bool debug = false;

void run_shell(void)
{
	while(true)
	{
		terminal_writestring(prefix);
		char* input = read_line();
		
		
		
		
		if(strcmp(input,"traps are gay") == 0)
		{
			terminal_writestring("\nOK, can we get ONE thing straight?\nAnybody, and I mean ANYBODY, who says this\n");
			terminal_writestring("is simply in denial of how straight they are.\nThey WANT to think that they are gay, but they aren't.\n");
			terminal_writestring("So there, scrub. Traps are 100% NOT GAY\n");
		}
		else if(strcmp(input, "clear") == 0)
			terminal_clear();
		else if(strcmp(input, "debug") == 0)
		{
			debug = !debug;
			terminal_writestring("Turning debug ");
			terminal_writestring(debug?"on":"off");
			terminal_writestring("\n");
		}
		else if(strcmp(input, "restart") == 0)
			restart();
		
		if(debug)
		{
			if(input == NULL)
			{
				terminal_writestring("Buffer contents: NULL\n");
				continue;
			}
			terminal_writestring("Buffer contents: ");
			terminal_writestring(input);
			terminal_writestring("\n");
		}
		
		
	}
}
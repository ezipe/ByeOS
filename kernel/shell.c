#include "shell.h"
#include <drivers/input/kbd.h>
#include <drivers/vga.h>
#include <drivers/power.h>
#include <stdlib.h>

static bool debug = false;

void run_shell(void)
{
	while(true)
	{
		terminal_writestring(prefix);
		char* input = read_line();
		
		
		
		
		if(strcmp(input,"traps are gay") == 0)
		{
			puts("\nOK, can we get ONE thing straight?\nAnybody, and I mean ANYBODY, who says this");
			puts("is simply in denial of how straight they are.\nThey WANT to think that they are gay, but they aren't.");
			puts("So there, scrub. Traps are 100% NOT GAY");
		}
		else if(strcmp(input, "clear") == 0)
			terminal_clear();
		else if(strcmp(input, "debug") == 0)
		{
			debug = !debug;
			puts("Turning debug ");
			puts(debug?"on":"off");
		}
		else if(strcmp(input, "restart") == 0)
			restart();
		
		if(debug)
		{
			if(input == NULL)
			{
				puts("Buffer contents: NULL\n");
				continue;
			}
			terminal_writestring("Buffer contents: ");
			terminal_writestring(input);
			terminal_writestring("\n");
		}
		
		
	}
}
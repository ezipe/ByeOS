#include "shell.h"
#include <drivers/input/kbd.h>
#include <drivers/vga.h>
#include <drivers/power.h>
#include <drivers/timer.h>
#include <libk.h>

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
		else if(strcmp(input, "timer") == 0)
			terminal_write_dec(get_tick());
		else if(strcmp(input, "laureloryanny") == 0)
		{
			while(true)
			{
				puts("laurel or yanny?");
				char* response = read_line();
				if(strcmp(response, "laurel") == 0)
				{
					puts("you are incredibly intelligent! congrats");
					break;
				}
				else if(strcmp(response, "yanny") == 0)
				{
					puts("silly child, its laurel! u stupid");
				}
			}
		}
		else if(strcmp(input, "help") == 0)
		{
			puts("ByeOS v0.0.1");
			puts("Commands list");
			puts("-------------------");
			puts("Command										Function\n");
			puts("traps are gay:								Explains to you how traps aren't gay.");
			puts("clear:										Clears the current text on shell.");
			puts("debug:										Toggles debug mode on and off.");
			puts("restart:										Reboots the system.");
			puts("timer:										Debug command that displays how many ticks have passed since boot.");
			puts("laureloryanny:								Initiates laurel or yanny question for user to answer.");
			puts("	laurel:										Tells you that you are intelligent.");
			puts("	yanny:										Tells you how stupid you are.");
		}
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
#include "kbd.h"
#include <x86/isr.h>
#include "../vga.h"
#include "cmd_queue.h"

static char res[256];

char read_char();

char* read_line()
{
	memset(res, 0, sizeof(res));
	state = WAITING;
	size_t index = 0;
	while(state != NEWLINE_RECEIVED)
	{
		char c = read_char();
		if(c == '\b')
		{
			if(index != 0)
				res[--index] = 0; 
			
				
		}
		else if(c && c != '\n')
			res[index++] = c;
		
	}
	
	
	
	return res;
}



char read_char()
{
	size_t index = buffer_pos % BUFFER_SIZE;
	
	while(scancode_buffer[index] == 0) ;
	uint8_t code = scancode_buffer[index];
	
	scancode_buffer[index] = 0;
	buffer_pos++;
	char res = 0;
	if(!(code & 0x80))
	{		
		if(state == BREAK_CODE_RECEIVED)
		{
			state = WAITING;
			return 0;
		}
		
		res = scancodes[code];
		
		if(res == '\n')
		{
			state = NEWLINE_RECEIVED;
		}
		else
		{
			state = WAITING;
		}
		
		terminal_putchar(res);
	}
	else
	{
		state = BREAK_CODE_RECEIVED;
	}
	
	
	
	return res;
}

void init_keyboard()
{
	buffer_pos = 0;
	init_keyboard_interrupt_handler();
}
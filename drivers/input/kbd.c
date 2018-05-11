#include "kbd.h"
#include <x86/isr.h>
#include "../vga.h"
#include "cmd_queue.h"

static char res[256];

char* read_line()
{
	is_reading = true;
	while(is_reading);
	
	
	if(char_index < 0){char_index = 0; return NULL; }
	
	memset(res, 0, 256);
	memcpy(input_buffer, res, char_index);
	memset(input_buffer, 0, char_index);
	
	char_index = 0;
	
	return res;
}

static char get_scancode()
{
	char c = 0;
	while(1)
	{
			if(inb(0x60)!=c)
			{
				c = inb(0x60);
				if(c>0)
					return c;
			}
	}
}

static void keyboard_callback(registers_t regs)
{

	char status = inb(0x64);
    char scancode = inb(0x60);
	
	if(scancode < 0) return;
	//kb is sending set 1 i have codes for set 2
	
	terminal_write_hex(scancode);
	terminal_putchar('\n');
	
	char ascii = scancodes[(size_t)scancode];	
	if(is_reading)
	{
		
			
		if(ascii == '\n') //if enter presssed
		{
			is_reading = false;
			terminal_putchar(ascii);
			return;
		}
		else if(ascii == '\b')
		{
			int32_t index = --char_index;
			if(index < 0)
			{			
				char_index++; 
				return;
			}
			
			
			input_buffer[index] = 0;
			terminal_putchar(ascii);
			return;
		}
		else if(isprint(ascii) || ascii == '\t') //we can have tab too, but nothing else
		{
			terminal_putchar(ascii);
			input_buffer[char_index++] = ascii;
		}
		else
		{
			//TODO: handle special chars
		}
		
	}
}

void init_keyboard()
{
	
	
	add_cmd(0x60, 0xF0);
	add_cmd(0x60, 1);
	
	
		
	
	
	register_interrupt_handler(IRQ1, &keyboard_callback);
}
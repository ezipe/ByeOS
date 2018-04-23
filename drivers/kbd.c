#include "kbd.h"
#include <x86/isr.h>
#include "vga.h"

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

static void keyboard_callback(registers_t regs)
{
	char status = inb(0x64);
    char scancode = inb(0x60);
	
	if(scancode > MAX_SCANCODE || scancode < 0)
		return;
	char ascii = scancodes[scancode];	
	if(is_reading)
	{
		
			
		if(ascii == '\n') //if enter presssed
		{
			is_reading = false;
			terminal_putchar(ascii);
			return;
		}
		if(ascii == '\b')
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
		else
		{
			terminal_putchar(ascii);
			input_buffer[char_index++] = ascii;
		}
	}
}

void init_keyboard()
{
	register_interrupt_handler(IRQ1, &keyboard_callback);
}
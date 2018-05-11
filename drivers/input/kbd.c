#include "kbd.h"
#include <x86/isr.h>
#include "../vga.h"
#include "cmd_queue.h"

static char res[256];



char* read_line()
{
	state = WAITING;
	while(state != NEWLINE_RECEIVED);
	
	
	memset(res, 0, 256);
	uint8_t index = 0;
	for(uint8_t* i = input_buffer; *i != 0; i++)
	{
		res[index++] = i;
	}
	
	memset(input_buffer, 0, char_index);
	
	char_index = 0;
	
	return res;
}

static uint8_t prev_scancode;

static void keyboard_callback(registers_t regs)
{

	char status = inb(0x64);
    char scancode = inb(0x60);
	
	if(state == WAITING)
	{
		
		state = SCANCODE_RECIEVED;
		prev_scancode = scancode;
		
	}
	else if(state == SCANCODE_RECIEVED)
	{
		input_buffer[(char_index++ % BUFFER_SIZE)] = prev_scancode;
		if(prev_scancode == 0x5A)
			state = NEWLINE_RECEIVED;
		else
			state = WAITING;
		
		state = WAITING;
	}
}

void init_keyboard()
{
	
	
	add_cmd(0x60, 0xF0);
	add_cmd(0x60, 1);
	
	
		
	
	
	register_interrupt_handler(IRQ1, &keyboard_callback);
}
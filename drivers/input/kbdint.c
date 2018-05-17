#include "kbdint.h"

#include "../vga.h"

static volatile size_t current_scancode_pos;

static void keyboard_callback(registers_t* regs)
{

	uint8_t status = inb(0x64);
    uint8_t scancode = inb(0x60);
	
	
	
//	terminal_write_hex(scancode);
//	terminal_putchar(' ');
	
	scancode_buffer[current_scancode_pos++ % BUFFER_SIZE] = scancode;
}

void init_keyboard_interrupt_handler()
{
	memset((uint8_t*)scancode_buffer, 0, BUFFER_SIZE);
	current_scancode_pos = 0;	
	register_interrupt_handler(IRQ1, &keyboard_callback);
}
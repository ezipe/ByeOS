#include "ps2.h"
#include "input/kbd.h"
#include <stdlib.h>

#define PS2_CMD 0x64
#define PS2_DATA 0x60

static uint8_t num_ps2 = 0;

static void ps2_wait_in()
{
	while(inb(PS2_CMD) & (1<<0)) ;
}

static void ps2_wait_out()
{
	while(inb(PS2_CMD) & (1<<1)) ;
}


int init_ps2()
{
	//disable
	outb(PS2_CMD, 0xAD);
	outb(PS2_CMD, 0xA7);
	
	inb(PS2_DATA); //flush buffer
	
	outb(PS2_CMD, 0x20);
	ps2_wait_in();
	uint8_t config = inb(PS2_DATA);
	
	if(((config >> 5) & 1) == 0)
		num_ps2 = 1;
	config &= ~(1<<0);
	config &= ~(1<<1);
	config &= ~(1<<6);
	
	outb(PS2_CMD, 0x60);
	ps2_wait_out();
	outb(PS2_DATA, config);
	
	ps2_wait_out();
	
	outb(PS2_CMD, 0xAA);
	ps2_wait_in();
	if(!inb(PS2_DATA, 0x55)) return 1;
	if(num_ps2 != 1)
	{
		outb(PS2_CMD, 0xA8);
		ps2_wait_out();
		outb(PS2_CMD, 0x20);
		ps2_wait_in();
		uint8_t config = inb(PS2_DATA);
		if((config >> 5) & 1) == 0)
		{
			num_ps2 = 1;
			
		}
		else
		{
			outb(PS2_CMD, 0xA7);
			num_ps2 = 2;
		}	
		
	}
	ps2_wait_out();
	outb(PS2_CMD, 0zAB);
	ps2_wait_in();
	uint8_t port1 = inb(PS2_DATA);
	if(!port1) return port1;
	if(num_ps2 == 2)
	{
		ps2_wait_out();
		outb(PS2_CMD, 0xA9);
		ps2_wait_in();
		uint8_t port2 = inb(PS2_DATA);
		if(!port2) return port2;
	}
	
	
	init_keyboard();
}
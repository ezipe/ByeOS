#include "ps2.h"
#include "input/kbd.h"
#include <stdlib.h>

#define PS2_CMD 0x64
#define PS2_DATA 0x60

#define PS2_P1 0x60
#define PS2_P2 0x60

#define MAX_PS2 2

static bool ps2_channels[MAX_PS2] = {0,0};

static void ps2_wait_in()
{
	while(inb(PS2_CMD) & (1<<0)) ;
}

static void ps2_wait_out()
{
	while(inb(PS2_CMD) & (1<<1)) ;
}


uint16_t init_ps2()
{
	asm volatile("cli");
	//disable
	outb(PS2_CMD, 0xAD);
	outb(PS2_CMD, 0xA7);
	
	inb(PS2_DATA); //flush buffer
	//set config
	outb(PS2_CMD, 0x20);
	ps2_wait_in();
	uint8_t config = inb(PS2_DATA);
	
	if(((config >> 5) & 1) == 0)
		num_ps2[0] = 1;
	
	config &= ~(1<<0);
	config &= ~(1<<1);
	config &= ~(1<<6);
	
	outb(PS2_CMD, 0x60);
	ps2_wait_out();
	outb(PS2_DATA, config);
	
	ps2_wait_out();
	
	//controller self test
	outb(PS2_CMD, 0xAA);
	ps2_wait_in();
	if(!inb(PS2_DATA, 0x55)) return -1;
	//channel test (1 or 2?)
	if(!num_ps2[0])
	{
		outb(PS2_CMD, 0xA8);
		ps2_wait_out();
		outb(PS2_CMD, 0x20);
		ps2_wait_in();
		uint8_t configNew = inb(PS2_DATA);
		if((configNew >> 5) & 1) == 0)
		{
			num_ps2[0] = 1;
			
		}
		else
		{
			outb(PS2_CMD, 0xA7);
			num_ps2[0] = 1;
			num_ps2[1] = 1;
		}	
		config = configNew;
	}
	//interface tests
	ps2_wait_out();
	outb(PS2_CMD, 0xAB);
	ps2_wait_in();
	uint8_t port1 = inb(PS2_DATA);
	if(!port1) return port1;
	if(num_ps2[1])
	{
		ps2_wait_out();
		outb(PS2_CMD, 0xA9);
		ps2_wait_in();
		uint8_t port2 = inb(PS2_DATA);
		if(!port2) return port2;
	}
	
	//enable devices
	
	if(num_ps2[0])
		config |= 1 << 0;
	if(num_ps2[1])
		config |= 1 << 1;
	
	
	ps2_wait_out();
	outb(PS2_CMD, 0x60);
	ps2_wait_out();
	outb(PS2_DATA, config);
	ps2_wait_out();
	
	if(num_ps2[0])
		outb(PS2_CMD, 0xAE);
	ps2_wait_out();
	if(num_ps2[1])
		outb(PS2_CMD, 0xA8); 
	
	
	
	//reset devices
	uint8_t p1Res, p2Res = 0;
	
	if(num_ps2[0])
	{
		ps2_wait_out();
		outb(PS2_P1, 0xFF);
		ps2_wait_in();
		p1Res = inb(PS2_P1);
	}
	ps2_wait_out();
	if(num_ps2[1])
	{
		outb(PS2_CMD, 0xD4);
		ps2_wait_out();
		outb(PS2_P2, 0xFF);
		ps2_wait_in();
		p2Res = inb(PS2_P1);
	}
	init_keyboard();
	asm volatile("sti");
	
	return ((uint16_t)p1Res<<8) | p2Res;
}
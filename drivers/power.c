#include "power.h"

#include <common.h>

void restart(void)
{
	uint8_t good = 0x02;
	while(good & 0x02)
		good = inb(0x64);
	outb(0x64, 0xFE);
	while(true)
		asm volatile("hlt");
}
#include "timer.h"

#include <x86/isr.h>
#include "vga.h"
#include "input/cmd_queue.h"



uint32_t tick = 0;

static void timer_callback(registers_t* regs)
{
	tick++;
	int res = run_cmds();
//	terminal_write_dec(res);
//	if((tick % 60) == 0)
//		terminal_write_dec(run_cmds());
}

uint32_t get_tick()
{
	return tick;
}

void init_timer(uint32_t frequency)
{
	register_interrupt_handler(IRQ0, &timer_callback);
	
	uint32_t divisor = 1193180 / frequency;
	
	outb(0x43, 0x36);
	
	uint8_t low = (uint8_t)(divisor & 0xFF);
	uint8_t high = (uint8_t)( (divisor>>8) & 0xFF);
	
	outb(0x40, low);
	outb(0x40, high);
}
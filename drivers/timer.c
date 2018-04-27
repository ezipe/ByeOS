#include "timer.h"

#include <x86/isr.h>
#include "vga.h"
#include "input/cmd_queue.h"

#define debug_breakpoint asm volatile("xchgw %bx, %bx")

uint32_t tick = 0;

static void timer_callback(registers_t regs)
{
	debug_breakpoint;
	tick++;
	int res = run_cmds();
	if(tick % 60 == 0)
	{
		terminal_write_dec(res);
		terminal_writestring("\n");
	}
//	terminal_writestring("Tick: ");
//    terminal_write_dec(tick);
//    terminal_writestring("\n");
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
#include "exceptions.h"

static void pagefault_callback(registers_t* regs)
{
	
	uint32_t faulting_address;
	asm volatile("mov %%cr2, %0" : "=r" (faulting_address));
	int present = !(regs->err_code & 0x1);
	int rw = regs->err_code & 0x2;
	int us = regs->err_code & 0x4;
	int reserved = regs->err_code & 0x8;
	int id = regs->err_code & 0x10;
	
	#ifdef DEBUG_REGS
	register_dump(regs);
	#endif
	
	terminal_writestring("Page fault! (");
	if(present) {terminal_writestring("present ");}
	if(rw) {terminal_writestring("read-only ");}
	if(us) {terminal_writestring("user-mode ");}
	if(reserved) {terminal_writestring("reserved ");}
	terminal_writestring(") at ");
	terminal_write_hex(faulting_address);
	terminal_writestring("\n");
	
	PANIC("Page Fault");
}

static void gpf_callback(registers_t* regs)
{
	#ifdef DEBUG_REGS
	register_dump(regs);
	#endif
	
	PANIC("GPF");
}

void enable_exception_handling()
{
	register_interrupt_handler(13, &gpf_callback);
	register_interrupt_handler(14, &pagefault_callback);
}


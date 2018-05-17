#include "exceptions.h"

static void pagefault_callback(registers_t* regs)
{
	puts("PAGE FAULT");
	#ifdef DEBUG_REGS
	register_dump(regs);
	#else
	terminal_writestring("ERROR CODE ");
	terminal_write_hex(regs->err_code);
	terminal_writestring("\n");
	#endif
	
	while(true)
	{	
		asm volatile("cli\n\t");
		asm volatile("hlt\n\t");
	}
}

static void gpf_callback(registers_t* regs)
{
	puts("GENERAL PROTECTION FAULT");
	#ifdef DEBUG_REGS
	register_dump(regs);
	#endif
	
	while(true)
	{	
		asm volatile("cli\n\t");
		asm volatile("hlt\n\t");
	}
}

void enable_exception_handling()
{
	register_interrupt_handler(13, &gpf_callback);
	register_interrupt_handler(14, &pagefault_callback);
}


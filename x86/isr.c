#include "isr.h"




void register_interrupt_handler(uint8_t n, isr_t handler)
{
	interrupt_handlers[n] = handler;
}


#ifdef DEBUG_REGS
void register_dump(registers_t* regs)
{

	terminal_writestring("BEGIN REGISTER DUMP: \n");
	terminal_writestring("DS: ");
	terminal_write_hex(regs->ds);
	terminal_writestring("\nEDI: ");
	terminal_write_hex(regs->edi);
	terminal_writestring("\nESI: ");
	terminal_write_hex(regs->esi);
	terminal_writestring("\nEBP: ");
	terminal_write_hex(regs->ebp);
	terminal_writestring("\nEBX: ");
	terminal_write_hex(regs->ebx);
	terminal_writestring("\nEDX: ");
	terminal_write_hex(regs->edx);
	terminal_writestring("\nECX: ");
	terminal_write_hex(regs->ecx);
	terminal_writestring("\nEAX: ");
	terminal_write_hex(regs->eax);
	terminal_writestring("\nERR CODE: ");
	terminal_write_hex(regs->err_code);
	terminal_writestring("\nEIP: ");
	terminal_write_hex(regs->eip);
	terminal_writestring("\nCS: ");
	terminal_write_hex(regs->cs);
	terminal_writestring("\nEFLAGS: ");
	terminal_write_hex(regs->eflags);
	terminal_writestring("\nESP: ");
	terminal_write_hex(regs->esp);
	terminal_writestring("\nSS: ");
	terminal_write_hex(regs->ss);
	terminal_writestring("\nEND REGISTER DUMP. LOOPING INFINITELY");

}
#endif
void isr_handler(registers_t* regs)
{
	
	if (interrupt_handlers[regs->int_no] != 0)
    {
        isr_t handler = interrupt_handlers[regs->int_no];
        handler(regs);
    }
	else
	{
		terminal_writestring("Unhandled interrupt caught: ");
		terminal_write_hex(regs->int_no);
		terminal_writestring("\n");
		
		register_dump(regs);
		
		PANIC("");
	}
}

void irq_handler(registers_t* regs)
{
	if(regs->int_no >= 40)
	{
		outb(0xA0, 0x20);
	}
	outb(0x20, 0x20);

	if(interrupt_handlers[regs->int_no] != 0)
	{
		isr_t handler = interrupt_handlers[regs->int_no];
		handler(regs);
	}
}
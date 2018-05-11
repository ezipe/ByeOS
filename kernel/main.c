#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#include "drivers/vga.h" 
#include "drivers/input/ps2.h"
#include "drivers/timer.h"
#include "x86/descriptor_tables.h"
#include "shell.h"
#include "multiboot.h" 
 
static uint64_t mem; 
 
void kmain(multiboot_info_t *mboot) 
{
	asm volatile("cli");
	
	init_descriptor_tables();
	
	
	terminal_initialize();
	terminal_setcolor(vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));

	
	terminal_write_hex(init_ps2());
	terminal_writestring("\n");
	
	init_timer(60);
	
	if(mboot->flags & (1<<0))
	{
		terminal_writestring("MEMORY: ");
		mem = ((uint64_t)mboot->mem_upper) + mboot->mem_lower;
		terminal_write_dec(mem / 1024);
		terminal_writestring(" MB\n");
	}
	
	asm volatile("sti");
	
	run_shell();
	
	while(1) 
		asm volatile("hlt\n\t");
}
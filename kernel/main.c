#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#include "drivers/vga.h" 
#include "drivers/kbd.h"
#include "x86/descriptor_tables.h"
#include "shell.h"
#include "multiboot.h" 
 
static uint64_t mem; 
 
void kmain(multiboot_info_t *mboot) 
{

	
	init_descriptor_tables();
	init_keyboard();
	
	terminal_initialize();
	terminal_setcolor(vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));

	if(mboot->flags & (1<<0))
	{
		terminal_writestring("MEMORY: ");
		mem = ((uint64_t)mboot->mem_upper) + mboot->mem_lower;
		terminal_write_dec(mem / 1024);
//		terminal_write_dec(mboot->mem_lower);
//		terminal_writestring(" KiB\nMEMORY UPPER: ");
//		terminal_write_dec(mboot->mem_upper);
		terminal_writestring(" MB\n");
	}
	
	asm volatile("sti");
	
	run_shell();
	
	while(1) __asm__("hlt\n\t");
}
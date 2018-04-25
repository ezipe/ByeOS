#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#include "drivers/vga.h" 
#include "drivers/input/kbd.h"
#include "x86/descriptor_tables.h"
#include "shell.h"
#include "multiboot.h" 
 
static uint64_t mem; 
 
void kmain(multiboot_info_t *mboot) 
{

	
	init_descriptor_tables();
	
	
	terminal_initialize();
	terminal_setcolor(vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));

	init_keyboard();
	
	if(mboot->flags & (1<<0))
	{
		terminal_writestring("MEMORY: ");
		mem = ((uint64_t)mboot->mem_upper) + mboot->mem_lower;
		terminal_write_dec(mem / 1024);
		terminal_writestring(" MB\n");
	}
	
	asm volatile("sti");
	
	puts("stdlib test!");
	
	run_shell();
	
	while(1) 
		asm volatile("hlt\n\t");
}
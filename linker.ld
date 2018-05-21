ENTRY(start)

SECTIONS
{
	KERNEL_VIRTUAL_BASE = 0xC0000000;
	. = KERNEL_VIRTUAL_BASE + 0x00100000;
	
	.text ALIGN(4K) : AT(ADDR(.text) - KERNEL_VIRTUAL_BASE)
	{
		*(.multiboot)
		*(.text)
	}
	
	.rodata ALIGN(4K) : AT(ADDR(.rodata) - KERNEL_VIRTUAL_BASE)
	{
		*(.rodata)
	}
	
	.data ALIGN(4K) : AT(ADDR(.data) - KERNEL_VIRTUAL_BASE)
	{
		*(.data)
	}
	
	.bss : AT(ADDR(.bss) - KERNEL_VIRTUAL_BASE)
	{
		*(COMMON)
		*(.bss)
		endkernel = .;
	}
	
	KERNEL_END = .;
}
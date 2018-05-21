; Basic GRUB Multiboot header (comments helpfully provided by OSdev.org)
; Constants for multiboot header
MBALIGN equ 1<<0 ; align loaded modules on page boundaries
MEMINFO equ 1<<1 ; provide memory map
FLAGS equ MBALIGN | MEMINFO ; this is the multiboot flag field
MAGIC equ 0x1BADB002 ; magic number lets bootloader find header
CHECKSUM equ -(MAGIC + FLAGS) ; checksum of everything above, to prove that this is multiboot compatible

KERNEL_VIRTUAL_BASE equ 0xC0000000

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .bss
align 16
stack_bottom:
	resb 16384 ; 16 KiB
stack_top:
	
section .text
global start
start:
	
	
	
	
	mov esp, stack_top


	push ebx ; load multiboot info

	extern kmain
	call kmain
	

		cli
.hang:  hlt
		jmp .hang
.end:
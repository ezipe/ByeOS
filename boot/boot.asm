; Basic GRUB Multiboot header (comments helpfully provided by OSdev.org)
; Constants for multiboot header
MBALIGN equ 1<<0 ; align loaded modules on page boundaries
MEMINFO equ 1<<1 ; provide memory map
FLAGS equ MBALIGN | MEMINFO ; this is the multiboot flag field
MAGIC equ 0x1BADB002 ; magic number lets bootloader find header
CHECKSUM equ -(MAGIC + FLAGS) ; checksum of everything above, to prove that this is multiboot compatible

KERNEL_VIRTUAL_BASE equ 0xC0000000
KERNEL_PAGE_NUMBER equ (KERNEL_VIRTUAL_BASE >> 22)

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

section .data
align 0x1000
BootPageDirectory:
	dd 0x00000083
	times (KERNEL_PAGE_NUMBER - 1) dd 0
	dd 0x00000083
	times (1024 - KERNEL_PAGE_NUMBER - 1) dd 0
	

section .text
global start
start:
	mov ecx, (BootPageDirectory - KERNEL_VIRTUAL_BASE)
	mov cr3, ecx
	
	mov ecx, cr4
	or ecx, 0x00000010
	mov cr4, ecx
	
	mov ecx, cr0
	or ecx, 0x80000000
	mov cr0, ecx
	
	lea ecx, [HigherHalf]
	jmp ecx
	
	
HigherHalf:	

	mov dword [BootPageDirectory], 0
	invlpg [0]
	
	mov esp, stack_top

	add ebx, KERNEL_VIRTUAL_BASE
	push ebx ; load multiboot info

	extern kmain
	call kmain
	

		cli
.hang:  hlt
		jmp .hang
.end:
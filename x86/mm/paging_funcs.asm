section .text

[GLOBAL set_page_directory]
set_page_directory:
	push ebp
	mov ebp, esp
	mov eax, [esp+8]
	mov cr3, eax
	mov esp, ebp
	pop ebp
	ret

	
[GLOBAL enable_paging]
enable_paging:
	push ebp
	mov ebp, esp
	mov eax, cr0
	or eax, 0x80000000
	mov cr0, eax
	mov esp, ebp
	pop ebp
	ret
	
[GLOBAL disable_paging]
disable_paging:
	push ebp
	mov ebp, esp
	mov eax, cr0
	and eax, ~(0x80000000)
	mov cr0, eax
	mov esp, ebp
	pop ebp
	ret
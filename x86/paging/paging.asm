[GLOBAL set_page_directory]
set_page_directory:
	mov eax, [esp+4]
	mov cr3, [eax]
	ret

	
[GLOBAL enable_paging]
enable_paging:
	mov eax, cr0
	or eax, 0x80000000
	mov cr0, eax
	ret
	
[GLOBAL disable_paging]
disable_paging:
	mov eax, cr0
	mov eax, cr0
	and eax, ~(0x80000000)
	mov cr0, eax
	ret
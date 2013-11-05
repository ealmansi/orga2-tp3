

	; cargar la tarea inicial

call tss_inicializar_inicial
	
	push eax
	
	call nueva_tss
	
	add esp, 4
	mov ax, 0x17
	ltr ax
	breakpoint

;~ extern arreglo_navios
;~ extern arreglo_banderas
extern init_tss

	; inicializar entradas de la gdt de las tsss

	mov eax, [arreglo_navios]
	push eax
	call init_tss
	add esp, 4
	
	mov eax, [arreglo_banderas]
	push eax
	call init_tss
	add esp, 4

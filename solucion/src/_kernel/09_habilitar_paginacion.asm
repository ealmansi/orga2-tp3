	; habilitar paginacion

	MOV 	eax, 0x27000
	MOV 	cr3, eax

	MOV 	eax, cr0
	OR		eax, 0x80000000
	MOV		cr0, eax

	CALL imprimirNombreEquipo


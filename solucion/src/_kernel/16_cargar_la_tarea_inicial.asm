

	; cargar la tarea inicial

	;mov dword 	ax, [GDT_DESC + 2] 		; ax <- &gdt
	;add 		ax, 0xB8 				; ax += 8 * GDT_IDX_TASK_INICIAL
	MOV ax, 0xC0;
	ltr ax 					; <-- ACA TIRA EXCEPCIONGP



	; cargar la tarea inicial

	MOV 	ax, 0xB8 				; ax = 8 * GDT_IDX_TASK_INICIAL
	LTR 	ax



	; configurar controlador de interrupciones

	call deshabilitar_pic
	call resetear_pic
	call habilitar_pic

	; habilitar interrupciones
	
	sti

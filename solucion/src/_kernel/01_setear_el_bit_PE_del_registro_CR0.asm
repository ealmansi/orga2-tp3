

	; setear el bit PE del registro CR0
	
	MOV 	eax, cr0
	OR  	eax, 1
	MOV 	cr0, eax
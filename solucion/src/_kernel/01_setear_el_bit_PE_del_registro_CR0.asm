	; setear el bit PE del registro CR0
	
	mov 	eax, cr0
	or  	eax, 1
	mov 	cr0, eax
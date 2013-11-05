extern tss_inicializar_idle
extern tss_inicializar_inicial
extern nueva_tss


	; inicializar tarea inicial
	
	
	; inicializar tarea idle
	
	call tss_inicializar_idle

	push eax
	
	call nueva_tss
	
	add esp, 4

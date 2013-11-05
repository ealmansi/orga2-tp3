extern tss_inicializar_idle
extern tss_inicializar_inicial
extern nueva_tss
global offset_idle

offset_idle: DW 0x0;
	; inicializar tarea inicial
		
	
	; inicializar tarea idle
	
	CALL 		tss_inicializar_idle

	PUSH 		eax
	
	CALL		nueva_tss
	;breakpoint
	MOV		 	[offset_idle], ax
	ADD 		esp, 4

	

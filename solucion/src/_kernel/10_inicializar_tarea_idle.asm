extern tss_inicializar_idle
extern tss_inicializar_inicial
extern nueva_tss
global offset_idle

	JMP empezarAca
offset_idle: DW 0x0;
	; inicializar tarea inicial
empezarAca:
	
	; inicializar tarea idle
	
	CALL 		tss_inicializar_idle

	PUSH 		eax
	
	CALL		nueva_tss
	MOV		 	[offset_idle], ax
	ADD 		esp, 4

	

extern mmu_inicializar_tareas

	; inicializar memoria de tareas
	
	CALL 	mmu_inicializar_tareas		; copia el código de las tareas
										; de tierra a mar, e inicializa
										; los directorios y tablas de
										; cada una

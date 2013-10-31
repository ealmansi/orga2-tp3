extern mmu_inicializar_dir_kernel
extern mmu_inicializar_tablas_kernel

	; inicializar el directorio de paginas
	
	CALL 	mmu_inicializar_dir_kernel
	
	CALL 	mmu_inicializar_tablas_kernel



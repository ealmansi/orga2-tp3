global arreglo_navios
global arreglo_banderas
extern tss_inicializar_navios
extern tss_inicializar_banderas

arreglo_navios: dw 0
arreglo_banderas: dw 0

	; inicializar todas las tsss


	call tss_inicializar_navios
	
	mov [arreglo_navios], eax
	
	call tss_inicializar_banderas
	
	mov [arreglo_banderas], eax

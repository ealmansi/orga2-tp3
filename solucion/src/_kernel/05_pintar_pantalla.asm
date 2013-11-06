extern inicializar_manejo_video;

    ; Limpiar pantalla

    MOV     ecx, 80*2*25            ; cantidad total de bytes de video

.limpiarPantalla:
    MOV     byte [fs:ecx-1], 0
    LOOP    .limpiarPantalla

    ; Setear primera y ultima filas en formato de letras blancas y fondo negro

    MOV     ecx, 80                 ; Cada fila tiene 80 caracteres. Con esto puedo hacer loop.
    XOR     ebx, ebx                ; Contador de posición primera fila
    MOV     edx, 80*2*24            ; Contador de posición ultima fila

.setearFormatoFilas:
    MOV     byte [fs:ebx+1], 00001111b
    MOV     byte [fs:edx+1], 00001111b
    ADD     edx, 2
    ADD     ebx, 2
    LOOP    .setearFormatoFilas

    ; Colorear pantalla    
    

	CALL inicializar_manejo_video

    CALL pintar_pantalla_modo_estado

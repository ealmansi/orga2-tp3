	; acomodar los segmentos
	
    xor		eax, eax
    mov		ax, 0000000010100000b       ; ds, gs, es, ss = { index: 20 | gdt/ldt: 0 | rpl: 00 }
    mov		ds, ax
    mov		gs, ax
    mov		es, ax
    mov		ss, ax
    mov		ax, 0000000010110000b       ; fs = { index: 22 | gdt/ldt: 0 | rpl: 00 }
    mov		fs, ax


	; acomodar los segmentos
	
    XOR		eax, eax
    MOV		ax, 0000000010100000b       ; ds, gs, es, ss = { index: 20 | gdt/ldt: 0 | rpl: 00 }
    MOV		ds, ax
    MOV		gs, ax
    MOV		es, ax
    MOV		ss, ax
    MOV		ax, 0000000010110000b       ; fs = { index: 22 | gdt/ldt: 0 | rpl: 00 }
    MOV		fs, ax
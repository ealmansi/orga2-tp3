	; inicializar la IDT

	call idt_inicializar

	lidt 		[IDT_DESC]

	;xor ecx, ecx
	;idiv ecx

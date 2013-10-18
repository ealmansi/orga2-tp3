	; inicializar la IDT

	CALL idt_inicializar

	LIDT 		[IDT_DESC]
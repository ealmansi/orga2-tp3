

    ; pasar a modo protegido
    
    JMP		0000000010010000b:mp        ; seteo cs = { index: 18 | gdt/ldt: 0 | rpl: 00 }

BITS 32

mp:
for i in "00_cargar_la_GDT" "01_setear_el_bit_PE_del_registro_CR0" "02_pasar_a_modo_protegido" "03_acomodar_los_segmentos" "04_setear_la_pila" "05_pintar_pantalla" "06_inicializar_el_manejador_de_memoria" "07_inicializar_el_directorio_de_paginas" "08_inicializar_memoria_de_tareas" "09_habilitar_paginacion" "10_inicializar_tarea_idle" "11_inicializar_todas_las_tsss" "12_inicializar_entradas_de_la_gdt_de_las_tsss" "13_inicializar_el_scheduler" "14_inicializar_la_IDT" "15_configurar_controlador_de_interrupciones" "16_cargar_la_tarea_inicial" "17_saltar_a_la_primer_tarea"
do
	touch "$i.asm"
done
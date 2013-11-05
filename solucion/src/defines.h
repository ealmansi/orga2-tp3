/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

    Definiciones globales del sistema.
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__

/* Bool */
/* -------------------------------------------------------------------------- */
#define TRUE                    0x00000001
#define FALSE                   0x00000000


/* Misc */
/* -------------------------------------------------------------------------- */
#define CANT_TAREAS             8

#define TAMANO_PAGINA           0x00001000

#define TASK_SIZE               (2 * TAMANO_PAGINA)


/* Indices en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_IDX_NULL_DESC           0

/* Direcciones de memoria */
/* -------------------------------------------------------------------------- */
#define BOOTSECTOR              0x00001000 /* direccion fisica de comienzo del bootsector (copiado) */
#define KERNEL                  0x00001200 /* direccion fisica de comienzo del kernel */
#define VIDEO                   0x000B8000 /* direccion fisica del buffer de video */

/* Direcciones virtuales de código, pila y datos */
/* -------------------------------------------------------------------------- */
#define TASK_CODE               0x40000000 /* direccion virtual del codigo */

#define TASK_IDLE_CODE          0x40000000 /* direccion virtual del codigo de la tarea idle */
#define TASK_IDLE_STACK         0x003D0000 /* direccion virtual de la pila de la tarea idle */

#define TASK_ANCLA              0x40002000
#define TASK_ANCLA_FIS          0x00000000

#define AREA_TIERRA_INICIO      0x00000000  /* 0.0 MB     */
#define AREA_TIERRA_FIN         0x000FFFFF  /* 1.0 MB - 1 */
#define AREA_MAR_INICIO         0x00100000  /* 1.0 MB     */
#define AREA_MAR_FIN            0x0077FFFF  /* 7.5 MB - 1 */

/* Direcciones de directorios, tablas de paginas y pilas nivel 0 de tareas */

#define TASK_1_PAGE_DIR 		0x00030000 /* direccion fisica para el directorio de paginas de la tarea 1 */
#define TASK_2_PAGE_DIR 		0x00031000 /* direccion fisica para el directorio de paginas de la tarea 2 */
#define TASK_3_PAGE_DIR 		0x00032000 /* direccion fisica para el directorio de paginas de la tarea 3 */
#define TASK_4_PAGE_DIR 		0x00033000 /* direccion fisica para el directorio de paginas de la tarea 4 */
#define TASK_5_PAGE_DIR 		0x00034000 /* direccion fisica para el directorio de paginas de la tarea 5 */
#define TASK_6_PAGE_DIR 		0x00035000 /* direccion fisica para el directorio de paginas de la tarea 6 */
#define TASK_7_PAGE_DIR 		0x00036000 /* direccion fisica para el directorio de paginas de la tarea 7 */
#define TASK_8_PAGE_DIR 		0x00037000 /* direccion fisica para el directorio de paginas de la tarea 8 */

#define TASK_1_PAGE_TABLE		0x00038000 /* direccion fisica para la tabla de paginas de la tarea 1 */


#define TASK_1_STACK_RING_0 	0x00040000 /* direccion fisica para la pila de nivel 0 de la tarea 1 */
#define TASK_2_STACK_RING_0 	0x00041000 /* direccion fisica para la pila de nivel 0 de la tarea 2 */
#define TASK_3_STACK_RING_0 	0x00042000 /* direccion fisica para la pila de nivel 0 de la tarea 3 */
#define TASK_4_STACK_RING_0 	0x00043000 /* direccion fisica para la pila de nivel 0 de la tarea 4 */
#define TASK_5_STACK_RING_0 	0x00044000 /* direccion fisica para la pila de nivel 0 de la tarea 5 */
#define TASK_6_STACK_RING_0 	0x00045000 /* direccion fisica para la pila de nivel 0 de la tarea 6 */
#define TASK_7_STACK_RING_0 	0x00046000 /* direccion fisica para la pila de nivel 0 de la tarea 7 */
#define TASK_8_STACK_RING_0 	0x00046000 /* direccion fisica para la pila de nivel 0 de la tarea 8 */

/* Direcciones fisicas de codigo en el mar */
#define TASK_1_CODE_ADDR		0X00100000
#define TASK_2_CODE_ADDR		0X00102000
#define TASK_3_CODE_ADDR		0X00104000
#define TASK_4_CODE_ADDR		0X00106000
#define TASK_5_CODE_ADDR		0X00108000
#define TASK_6_CODE_ADDR		0X0010A000
#define TASK_7_CODE_ADDR		0X0010C000
#define TASK_8_CODE_ADDR		0X0010E000

/* Direcciones fisicas de codigos */
/* -------------------------------------------------------------------------- */
/* En estas direcciones estan los códigos de todas las tareas. De aqui se
 * copiaran al destino indicado por TASK_<i>_CODE_ADDR.
 */
#define TASK_1_CODE_SRC_ADDR    0x00010000
#define TASK_2_CODE_SRC_ADDR    0x00012000
#define TAKS_3_CODE_SRC_ADDR    0x00014000
#define TASK_4_CODE_SRC_ADDR    0x00016000
#define TASK_5_CODE_SRC_ADDR    0x00018000
#define TASK_6_CODE_SRC_ADDR    0x0001A000
#define TASK_7_CODE_SRC_ADDR    0x0001C000
#define TASK_8_CODE_SRC_ADDR    0x0001E000

#define TASK_IDLE_CODE_SRC_ADDR 0x00020000


/* mapa de memoria fisica */

#define ADDR_BOOTSECTOR              	0x00001000

#define ADDR_KERNEL_CODE             	0x00001200

#define ADDR_TASK_1_CODE    			0x00010000
#define ADDR_TASK_2_CODE    			0x00012000
#define ADDR_TAKS_3_CODE    			0x00014000
#define ADDR_TASK_4_CODE    			0x00016000
#define ADDR_TASK_5_CODE    			0x00018000
#define ADDR_TASK_6_CODE    			0x0001A000
#define ADDR_TASK_7_CODE    			0x0001C000
#define ADDR_TASK_8_CODE    			0x0001E000

#define ADDR_TASK_IDLE_CODE 			0x00020000

#define ADDR_KERNEL_STACK				0x00027000

#define ADDR_KERNEL_PAGE_DIREC			0x00027000

#define ADDR_KERNEL_PAGE_TABLE_1		0x00028000

#define ADDR_TASK_IDLE_STACK_PL_0		0x0002A000

#define ADDR_KERNEL_PAGE_TABLE_2 		0x0002A000

#define ADDR_BUFFER_VIDEO_ESTADO 		0x0002D000
#define ADDR_BUFFER_VIDEO_MAPA 			0x0002E000

#define ADDR_TASK_1_PAGE_DIREC 			0x00030000
#define ADDR_TASK_2_PAGE_DIREC 			0x00031000
#define ADDR_TASK_3_PAGE_DIREC 			0x00032000
#define ADDR_TASK_4_PAGE_DIREC 			0x00033000
#define ADDR_TASK_5_PAGE_DIREC 			0x00034000
#define ADDR_TASK_6_PAGE_DIREC 			0x00035000
#define ADDR_TASK_7_PAGE_DIREC 			0x00036000
#define ADDR_TASK_8_PAGE_DIREC 			0x00037000

#define ADDR_TASK_1_PAGE_TABLE_1		0x00038000
#define ADDR_TASK_1_PAGE_TABLE_2		0x00039000
#define ADDR_TASK_2_PAGE_TABLE_1		0x0003A000
#define ADDR_TASK_2_PAGE_TABLE_2		0x0003B000
#define ADDR_TASK_3_PAGE_TABLE_1		0x0003C000
#define ADDR_TASK_3_PAGE_TABLE_2		0x0003D000
#define ADDR_TASK_4_PAGE_TABLE_1		0x0003E000
#define ADDR_TASK_4_PAGE_TABLE_2		0x0003F000
#define ADDR_TASK_5_PAGE_TABLE_1		0x00040000
#define ADDR_TASK_5_PAGE_TABLE_2		0x00041000
#define ADDR_TASK_6_PAGE_TABLE_1		0x00042000
#define ADDR_TASK_6_PAGE_TABLE_2		0x00043000
#define ADDR_TASK_7_PAGE_TABLE_1		0x00044000
#define ADDR_TASK_7_PAGE_TABLE_2		0x00045000
#define ADDR_TASK_8_PAGE_TABLE_1		0x00046000
#define ADDR_TASK_8_PAGE_TABLE_2		0x00047000

#define ADDR_TASK_1_STACK_PL_0			0x00049000
#define ADDR_TASK_2_STACK_PL_0			0x0004A000
#define ADDR_TASK_3_STACK_PL_0			0x0004B000
#define ADDR_TASK_4_STACK_PL_0			0x0004C000
#define ADDR_TASK_5_STACK_PL_0			0x0004D000
#define ADDR_TASK_6_STACK_PL_0			0x0004E000
#define ADDR_TASK_7_STACK_PL_0			0x0004F000
#define ADDR_TASK_8_STACK_PL_0			0x00050000

#define ADDR_MEM_VIDEO                 	0x000B8000

#define ADDR_VIRTUAL_TASK_CODE          0x40000000

/* macro para extraer bits
	BITS(hasta, desde, num): bits desde 'desde' inclusive hasta 'hasta' NO inclusive
	BITS(4, 1, 0b10101011101) == 0b110
*/

typedef unsigned int dword_t;
typedef unsigned short word_t;
typedef unsigned char byte_t;
typedef unsigned long long int bits_t;


#define BITS(h, d, num) ((bits_t)(((num) & ((1ull << (h)) - 1ull)) >> (d)))


#endif  /* !__DEFINES_H__ */

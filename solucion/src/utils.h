/* Funciones miscelaneas de mucha utilidad */

#ifndef __UTILS_H__
#define __UTILS_H__


void memcpy(void* dst, void* src, int size);
void memclear(void* dst, int size);
int strlen(char* str);
int int_size(int num);

#define min(a, b) (((a) < (b)) ? (a) : (b))

int obtener_indice_tarea_en_ejecucion();
int es_navio(int indice);
int es_bandera(int indice);
int numero_tarea(int indice);

#endif /* !__UTILS_H__ */

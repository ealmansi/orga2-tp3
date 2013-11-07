/* Funciones miscelaneas de mucha utilidad */

#ifndef __UTILS_H__
#define __UTILS_H__


void memcpy(void* dst, void* src, int size);
void memclear(void* dst, int size);
int strlen(char* str);
int int_size(int num);

#define min(a, b) (((a) < (b)) ? (a) : (b))

#endif /* !__UTILS_H__ */

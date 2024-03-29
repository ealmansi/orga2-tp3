/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#ifndef __GAME_H__
#define __GAME_H__

#include "defines.h"

unsigned int game_fondear(unsigned int dir);
unsigned int game_canonear(unsigned int dir_usuario, unsigned int dir_relativa);
unsigned int game_navegar(unsigned int dir_primera_pag_fisica, unsigned int dir_segunda_pag_fisica, unsigned int dir_ult_p1, unsigned int dir_ult_p2);

#endif  /* !__GAME_H__ */

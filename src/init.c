#include "codexion.h"

/*
** init.c  (5/5 functions)
**
**   int  init_sim(t_sim *sim, t_params *p)
**       -> memset sim, copy params, call the alloc/init functions below
**   static int  alloc_coders(t_sim *sim)
**       -> malloc array of t_coder (number_of_coders)
**   static int  alloc_dongles(t_sim *sim)
**       -> malloc array of t_dongle (1 dongle if 1 coder)
**   static void init_coders(t_sim *sim)
**       -> set id (1..N), left/right dongle pointers, last_compile = start
**   static int  init_dongles(t_sim *sim)
**       -> heap_init for each dongle, released_at = 0, holder = 0
*/

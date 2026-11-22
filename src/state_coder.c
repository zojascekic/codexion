#include "codexion.h"

/*
** state_coder.c  (4/5 functions)
**
**   long  get_last_compile(t_coder *c)
**       -> read under c->mutex
**   void  set_last_compile(t_coder *c, long t)
**       -> write under c->mutex (at compile START)
**   int   get_compile_count(t_coder *c)
**       -> read under c->mutex
**   void  inc_compile_count(t_coder *c)
**       -> ++ under c->mutex
*/

#include "codexion.h"

/*
** state.c  (2/5 functions)
**
**   int   is_stopped(t_sim *sim)
**       -> lock stop_mutex, read flag, unlock
**   void  set_stopped(t_sim *sim)
**       -> lock stop_mutex, flag = 1, unlock
*/

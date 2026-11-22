#include "codexion.h"

/*
** init_sync.c  (4/5 functions)
**
**   int  init_sync(t_sim *sim)
**       -> call the three functions below in order
**   static int  init_global_mutexes(t_sim *sim)
**       -> print_mutex + stop_mutex (stored in sim, NOT global variables)
**   static int  init_coder_mutexes(t_sim *sim)
**       -> one mutex per coder (protects last_compile + compile_count)
**   static int  init_dongle_sync(t_sim *sim)
**       -> one mutex + one cond per dongle
*/

#include "codexion.h"

/*
** cleanup.c  (4/5 functions)
**
**   void cleanup(t_sim *sim)
**       -> call the functions below; safe on partially initialised sim
**   static void destroy_dongles(t_sim *sim)
**       -> mutex/cond destroy + heap_free for each dongle, free array
**   static void destroy_coders(t_sim *sim)
**       -> mutex destroy for each coder, free array
**   static void destroy_global_mutexes(t_sim *sim)
**       -> destroy print_mutex + stop_mutex
*/

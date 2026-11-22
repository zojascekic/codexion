#include "codexion.h"

/*
** threads.c  (4/5 functions)
**
**   int  start_coders(t_sim *sim)
**       -> pthread_create for each coder with coder_routine
**   int  start_monitor(t_sim *sim)
**       -> pthread_create the monitor with monitor_routine
**   void join_all(t_sim *sim)
**       -> pthread_join every coder thread that was created + the monitor
**   void abort_start(t_sim *sim, int created)
**       -> on create failure: set_stopped, wake all, join the 'created' threads
*/

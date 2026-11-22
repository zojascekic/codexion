#include "codexion.h"

/*
** log.c  (2/5 functions)
**
**   void  log_state(t_coder *c, const char *msg)
**       -> lock print_mutex; if !is_stopped printf "%ld %d %s\n"; unlock
**   void  log_burnout(t_sim *sim, int id)
**       -> lock print_mutex; print "burned out" (called by monitor right after set_stopped); unlock
*/

#include "codexion.h"

/*
** scheduler.c  (4/5 functions)
**
**   int   compare_requests(t_request *a, t_request *b, t_sched s)
**       -> <0 if a goes first; switch on s -> fifo / edf
**   static int  compare_fifo(t_request *a, t_request *b)
**       -> smaller arrival seq first   (LIFO recode: bigger seq first)
**   static int  compare_edf(t_request *a, t_request *b)
**       -> smaller deadline first, tie-break -> compare_fifo / coder id
**   long  next_seq(t_sim *sim)
**       -> global-in-sim arrival counter, incremented under a mutex
*/

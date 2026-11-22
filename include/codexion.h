#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/* ---------------------------------------------------------------- */
/*  Types (to define)                                               */
/*    t_params    : the 8 parsed arguments (+ scheduler enum)        */
/*    t_request   : heap entry (coder id, priority key, arrival seq) */
/*    t_heap      : priority queue used by each dongle               */
/*    t_dongle    : mutex, cond, holder, released_at, wait queue     */
/*    t_coder     : id, thread, left/right dongle, last_compile,     */
/*                  compile_count, own mutex, ptr to t_sim           */
/*    t_sim       : params, coders, dongles, log mutex, stop flag,   */
/*                  start time, monitor thread                       */
/* ---------------------------------------------------------------- */

/* parsing.c       */
/* init.c          */
/* init_sync.c     */
/* threads.c       */
/* cleanup.c       */
/* time.c          */
/* log.c           */
/* state.c         */
/* state_coder.c   */
/* heap.c          */
/* heap_utils.c    */
/* scheduler.c     */
/* dongle.c        */
/* dongle_wait.c   */
/* coder.c         */
/* coder_actions.c */
/* monitor.c       */

#endif

#include "codexion.h"

/*
** heap.c  (5/5 functions)
**
**   int   heap_init(t_heap *h, int capacity)
**       -> malloc array of t_request, size = 0
**   int   heap_push(t_heap *h, t_request req, t_sched s)
**       -> add at end, sift_up
**   t_request heap_pop(t_heap *h, t_sched s)
**       -> take root, move last to root, sift_down
**   t_request *heap_peek(t_heap *h)
**       -> return root or NULL if empty (used for 'is it my turn?')
**   void  heap_free(t_heap *h)
**       -> free array
*/

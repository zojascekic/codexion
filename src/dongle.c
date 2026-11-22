#include "codexion.h"

/*
** dongle.c  (5/5 functions)
**
**   int   take_both(t_coder *c)
**       -> lock order: lower-index dongle first, then the other; log each take
**   int   dongle_request(t_dongle *d, t_coder *c)
**       -> build t_request (seq, deadline), heap_push under d->mutex
**   int   dongle_take(t_dongle *d, t_coder *c)
**       -> wait_for_dongle, then pop, holder = c->id; 0 if stopped
**   void  dongle_release(t_dongle *d)
**       -> holder = 0, released_at = now, cond_broadcast
**   void  release_both(t_coder *c)
**       -> dongle_release on both dongles
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:01:39 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/22 14:01:40 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** dongle.c  (5/5 functions)
**
**   int   take_both(t_coder *c)
**       -> lock order: lower-index dongle first, then the other; log each take
**   int   dongle_request(t_dongle *d, t_coder *c)
**       -> under d->mutex: seq = d->next_seq++, deadline = last_compile + t_burnout, heap_push
**   int   dongle_take(t_dongle *d, t_coder *c)
**       -> wait_for_dongle, then pop, holder = c->id; 0 if stopped
**   void  dongle_release(t_dongle *d)
**       -> holder = 0, released_at = now, cond_broadcast
**   void  release_both(t_coder *c)
**       -> dongle_release on both dongles
*/

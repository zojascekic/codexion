/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:01:39 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/25 08:19:52 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** dongle.c  (5/5 functions)
**
**   static void  dongle_request(t_dongle *d, t_coder *c)  join the line
**   static int   dongle_take(t_dongle *d, t_coder *c)     wait, then take
**   static void  dongle_release(t_dongle *d)              put down + bell
**   int          take_both(t_coder *c)                    first, then second
**   void         release_both(t_coder *c)
**
** Lock order: d->mutex, then (inside) c->mutex / stop_mutex. Never reverse.
*/

static void	dongle_request(t_dongle *d, t_coder *c)
{
	t_request	req;

	req.coder_id = c->id;
	req.seq = d->next_seq;
	d->next_seq++;
	req.deadline = get_last_compile(c) + c->sim->p.t_burnout;
	heap_push(&d->queue, req, c->sim->p.sched);
}

static int	dongle_take(t_dongle *d, t_coder *c)
{
	pthread_mutex_lock(&d->mutex);
	dongle_request(d, c);
	if (!wait_for_dongle(d, c))
	{
		pthread_mutex_unlock(&d->mutex);
		return (0);
	}
	heap_pop(&d->queue, c->sim->p.sched);
	d->holder = c->id;
	pthread_mutex_unlock(&d->mutex);
	log_state(c, "has taken a dongle");
	return (1);
}

static void	dongle_release(t_dongle *d)
{
	pthread_mutex_lock(&d->mutex);
	d->holder = 0;
	d->released_at = get_time_ms();
	pthread_cond_broadcast(&d->cond);
	pthread_mutex_unlock(&d->mutex);
}

int	take_both(t_coder *c)
{
	if (!dongle_take(c->first, c))
		return (0);
	if (!dongle_take(c->second, c))
	{
		dongle_release(c->first);
		return (0);
	}
	return (1);
}

void	release_both(t_coder *c)
{
	dongle_release(c->second);
	dongle_release(c->first);
}

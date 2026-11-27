/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zscekic <zscekic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:01:39 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/27 11:17:19 by zscekic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** dongle.c  (5/5 functions)
**
**   static long  new_ticket(t_coder *c)                     place in line
**   static void  dongle_request(t_dongle *d, t_coder *c, long ticket)
**   static void  dongle_release(t_dongle *d)                put down + bell
**   int          take_both(t_coder *c)       both at once, never just one
**   void         release_both(t_coder *c)
**
** Lock order: first->mutex, then second->mutex, then (inside)
** c->mutex / stop_mutex. Never reverse.
*/

/*
** Ticket = time of the request in microseconds, x1000 + coder id so two
** tickets are never equal. The SAME ticket goes into both queues, so the
** order of waiting coders is the same on every dongle.
*/
static long	new_ticket(t_coder *c)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000000L + tv.tv_usec) * 1000 + c->id);
}

static void	dongle_request(t_dongle *d, t_coder *c, long ticket)
{
	t_request	req;

	req.coder_id = c->id;
	req.seq = ticket;
	req.deadline = get_last_compile(c) + c->sim->p.t_burnout;
	pthread_mutex_lock(&d->mutex);
	heap_push(&d->queue, req, c->sim->p.sched);
	pthread_mutex_unlock(&d->mutex);
}

static void	dongle_release(t_dongle *d)
{
	pthread_mutex_lock(&d->mutex);
	d->holder = 0;
	d->released_at = get_time_ms();
	pthread_cond_broadcast(&d->cond);
	pthread_mutex_unlock(&d->mutex);
}

/*
** Join both lines, then wait (holding NO dongle) until both are mine.
** Only then take both together: nobody ever holds one dongle and waits.
*/
int	take_both(t_coder *c)
{
	long	ticket;
	int		ok;

	if (c->first == c->second)
		return (wait_alone(c));
	ticket = new_ticket(c);
	dongle_request(c->first, c, ticket);
	dongle_request(c->second, c, ticket);
	pthread_mutex_lock(&c->first->mutex);
	pthread_mutex_lock(&c->second->mutex);
	ok = wait_for_both(c);
	if (ok)
	{
		heap_pop(&c->first->queue, c->sim->p.sched);
		heap_pop(&c->second->queue, c->sim->p.sched);
		c->first->holder = c->id;
		c->second->holder = c->id;
	}
	pthread_mutex_unlock(&c->second->mutex);
	pthread_mutex_unlock(&c->first->mutex);
	if (!ok)
		return (0);
	log_state(c, "has taken a dongle");
	log_state(c, "has taken a dongle");
	return (1);
}

void	release_both(t_coder *c)
{
	dongle_release(c->second);
	dongle_release(c->first);
}

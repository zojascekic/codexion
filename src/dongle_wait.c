/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_wait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zscekic <zscekic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:01:35 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/27 11:17:19 by zscekic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** dongle_wait.c  (5/5 functions)
**
**   static long  ready_at(t_dongle *d, t_coder *c)      end of cooldown
**   static int   is_my_turn(t_dongle *d, t_coder *c)
**   static void  sleep_on(t_dongle *block, t_dongle *other, t_coder *c)
**   int          wait_for_both(t_coder *c)    holds both dongle mutexes
**   int          wait_alone(t_coder *c)       1 coder: wait for the end
*/

static long	ready_at(t_dongle *d, t_coder *c)
{
	return (d->released_at + c->sim->p.cooldown);
}

/*
** My turn = I am first in its queue + nobody holds it + cooled down.
*/
static int	is_my_turn(t_dongle *d, t_coder *c)
{
	t_request	*top;

	top = heap_peek(&d->queue);
	if (!top || top->coder_id != c->id)
		return (0);
	if (d->holder != 0)
		return (0);
	return (get_time_ms() >= ready_at(d, c));
}

/*
** Sleep on the bell of the dongle that blocks me (let the other go).
** Free but cooling down: nobody rings when the cooldown ends, so set
** an alarm (timedwait). Otherwise wait for a bell (cond_wait).
** Then take both mutexes back, in the usual order.
*/
static void	sleep_on(t_dongle *block, t_dongle *other, t_coder *c)
{
	struct timespec	alarm;

	pthread_mutex_unlock(&other->mutex);
	if (block->holder == 0 && get_time_ms() < ready_at(block, c))
	{
		ms_to_timespec(ready_at(block, c), &alarm);
		pthread_cond_timedwait(&block->cond, &block->mutex, &alarm);
	}
	else
		pthread_cond_wait(&block->cond, &block->mutex);
	pthread_mutex_unlock(&block->mutex);
	pthread_mutex_lock(&c->first->mutex);
	pthread_mutex_lock(&c->second->mutex);
}

/*
** Called (and returns) holding first->mutex and second->mutex.
** 1 = both dongles are mine to take, 0 = the simulation stopped.
*/
int	wait_for_both(t_coder *c)
{
	while (!is_stopped(c->sim))
	{
		if (!is_my_turn(c->first, c))
			sleep_on(c->first, c->second, c);
		else if (!is_my_turn(c->second, c))
			sleep_on(c->second, c->first, c);
		else
			return (1);
	}
	return (0);
}

/*
** 1 coder = 1 dongle on the table: take it, then wait for the monitor
** to stop us (wake_all rings this bell). Can never compile.
*/
int	wait_alone(t_coder *c)
{
	pthread_mutex_lock(&c->first->mutex);
	c->first->holder = c->id;
	pthread_mutex_unlock(&c->first->mutex);
	log_state(c, "has taken a dongle");
	pthread_mutex_lock(&c->first->mutex);
	while (!is_stopped(c->sim))
		pthread_cond_wait(&c->first->cond, &c->first->mutex);
	c->first->holder = 0;
	pthread_mutex_unlock(&c->first->mutex);
	return (0);
}

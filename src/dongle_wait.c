/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_wait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:01:35 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/25 08:20:00 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** dongle_wait.c  (2/5 functions, cooldown comes on Day 4)
**
**   static int  is_my_turn(t_dongle *d, t_coder *c)
**   int         wait_for_dongle(t_dongle *d, t_coder *c)
**
** Both are called while the caller HOLDS d->mutex.
*/

static int	is_my_turn(t_dongle *d, t_coder *c)
{
	t_request	*top;

	top = heap_peek(&d->queue);
	if (!top || top->coder_id != c->id)
		return (0);
	return (d->holder == 0);
}

/*
** Sleep in the dongle's waiting room until it is my turn.
** cond_wait gives d->mutex back while sleeping, takes it back on wake.
** Returns 0 if the simulation stopped while waiting.
*/
int	wait_for_dongle(t_dongle *d, t_coder *c)
{
	while (!is_my_turn(d, c))
	{
		if (is_stopped(c->sim))
			return (0);
		pthread_cond_wait(&d->cond, &d->mutex);
	}
	return (1);
}

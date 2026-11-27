/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sync.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zscekic <zscekic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:01:51 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/27 11:17:20 by zscekic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** init_sync.c  (4/5 functions)
**
**   int         init_sync(t_sim *sim)
**   static int  init_global_mutexes(t_sim *sim)
**   static int  init_coder_mutexes(t_sim *sim)
**   static int  init_dongle_sync(t_sim *sim)
**
** Every successful init is counted in a "receipt" (sim->sync_*),
** so cleanup destroys exactly what was created, nothing more.
*/

static int	init_global_mutexes(t_sim *sim)
{
	if (pthread_mutex_init(&sim->print_mutex, NULL) != 0)
		return (0);
	sim->sync_globals = 1;
	if (pthread_mutex_init(&sim->stop_mutex, NULL) != 0)
		return (0);
	sim->sync_globals = 2;
	return (1);
}

static int	init_coder_mutexes(t_sim *sim)
{
	t_coder	*c;

	while (sim->sync_coders < sim->p.n_coders)
	{
		c = &sim->coders[sim->sync_coders];
		if (pthread_mutex_init(&c->mutex, NULL) != 0)
			return (0);
		sim->sync_coders++;
	}
	return (1);
}

static int	init_dongle_sync(t_sim *sim)
{
	t_dongle	*d;

	while (sim->sync_dongles < sim->n_dongles)
	{
		d = &sim->dongles[sim->sync_dongles];
		if (pthread_mutex_init(&d->mutex, NULL) != 0)
			return (0);
		if (pthread_cond_init(&d->cond, NULL) != 0)
		{
			pthread_mutex_destroy(&d->mutex);
			return (0);
		}
		sim->sync_dongles++;
	}
	return (1);
}

int	init_sync(t_sim *sim)
{
	if (!init_global_mutexes(sim))
		return (0);
	if (!init_coder_mutexes(sim))
		return (0);
	return (init_dongle_sync(sim));
}

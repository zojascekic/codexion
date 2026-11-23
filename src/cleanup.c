/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:01:13 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/22 21:43:09 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** cleanup.c  (4/5 functions)
**
**   void         cleanup(t_sim *sim)
**   static void  destroy_dongles(t_sim *sim)
**   static void  destroy_coders(t_sim *sim)
**   static void  destroy_global_mutexes(t_sim *sim)
**
** Safe on a half-built sim: mutex loops only go up to the receipts,
** and free(NULL) does nothing (heaps never created have data = NULL).
*/

static void	destroy_dongles(t_sim *sim)
{
	int	i;

	if (!sim->dongles)
		return ;
	i = 0;
	while (i < sim->n_dongles)
	{
		if (i < sim->sync_dongles)
		{
			pthread_mutex_destroy(&sim->dongles[i].mutex);
			pthread_cond_destroy(&sim->dongles[i].cond);
		}
		heap_free(&sim->dongles[i].queue);
		i++;
	}
	free(sim->dongles);
	sim->dongles = NULL;
}

static void	destroy_coders(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->sync_coders)
	{
		pthread_mutex_destroy(&sim->coders[i].mutex);
		i++;
	}
	free(sim->coders);
	sim->coders = NULL;
}

static void	destroy_global_mutexes(t_sim *sim)
{
	if (sim->sync_globals >= 2)
		pthread_mutex_destroy(&sim->stop_mutex);
	if (sim->sync_globals >= 1)
		pthread_mutex_destroy(&sim->print_mutex);
}

void	cleanup(t_sim *sim)
{
	destroy_dongles(sim);
	destroy_coders(sim);
	destroy_global_mutexes(sim);
}

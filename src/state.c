/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:02:25 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/25 12:15:58 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** state.c  (2/5 functions)
**
**   int   is_stopped(t_sim *sim)     read  sim->stopped under stop_mutex
**   void  set_stopped(t_sim *sim)    write sim->stopped under stop_mutex
**
**   Nobody touches sim->stopped directly: always through these two.
*/

int	is_stopped(t_sim *sim)
{
	int	stopped;

	pthread_mutex_lock(&sim->stop_mutex);
	stopped = sim->stopped;
	pthread_mutex_unlock(&sim->stop_mutex);
	return (stopped);
}

void	set_stopped(t_sim *sim)
{
	pthread_mutex_lock(&sim->stop_mutex);
	sim->stopped = 1;
	pthread_mutex_unlock(&sim->stop_mutex);
}

/*
** Ring the bell of every dongle, so sleeping coders wake up and
** notice the stop flag. Lock each dongle so no wake-up gets lost.
*/
void	wake_all(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->n_dongles)
	{
		pthread_mutex_lock(&sim->dongles[i].mutex);
		pthread_cond_broadcast(&sim->dongles[i].cond);
		pthread_mutex_unlock(&sim->dongles[i].mutex);
		i++;
	}
}

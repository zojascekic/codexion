/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:02:25 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/22 14:02:26 by Zoja             ###   ########.fr       */
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

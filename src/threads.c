/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:02:29 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/25 08:26:07 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** threads.c  (2/5 functions, start_monitor comes on Day 4)
**
**   int   start_coders(t_sim *sim)          returns how many started
**   void  join_coders(t_sim *sim, int n)    wait for the first n coders
*/

int	start_coders(t_sim *sim)
{
	int		i;
	t_coder	*c;

	i = 0;
	while (i < sim->p.n_coders)
	{
		c = &sim->coders[i];
		if (pthread_create(&c->thread, NULL, coder_routine, c) != 0)
			return (i);
		i++;
	}
	return (i);
}

void	join_coders(t_sim *sim, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(sim->coders[i].thread, NULL);
		i++;
	}
}

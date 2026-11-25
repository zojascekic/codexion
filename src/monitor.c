/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:02:07 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/25 15:58:37 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** monitor.c  (3/5 functions)
**
**   static int  check_burnout(t_sim *sim)   1 if a coder burned out
**   static int  all_done(t_sim *sim)        1 if everyone compiled enough
**   void        *monitor_routine(void *arg) the referee thread
**
** The monitor only READS coder data, through the locked getters.
*/

static int	check_burnout(t_sim *sim)
{
	int		i;
	t_coder	*c;

	i = 0;
	while (i < sim->p.n_coders)
	{
		c = &sim->coders[i];
		if (get_time_ms() - get_last_compile(c) >= sim->p.t_burnout)
		{
			log_burnout(sim, c->id);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	all_done(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->p.n_coders)
	{
		if (get_compile_count(&sim->coders[i]) < sim->p.compiles_required)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_sim	*sim;

	sim = (t_sim *)arg;
	while (1)
	{
		if (check_burnout(sim))
			break ;
		if (all_done(sim))
		{
			set_stopped(sim);
			break ;
		}
		usleep(1000);
	}
	wake_all(sim);
	return (NULL);
}

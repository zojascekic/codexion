/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:01:59 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/22 14:02:00 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** log.c  (2/5 functions)
**
**   void  log_state(t_coder *c, const char *msg)
**         under print_mutex: print only if the simulation is still running
**   void  log_burnout(t_sim *sim, int id)
**         under print_mutex: set stopped FIRST, then print "burned out"
**         -> every later log_state sees stopped and prints nothing
**
**   Lock order is always print_mutex -> stop_mutex (never the reverse).
*/

void	log_state(t_coder *c, const char *msg)
{
	t_sim	*sim;

	sim = c->sim;
	pthread_mutex_lock(&sim->print_mutex);
	if (!is_stopped(sim))
		printf("%ld %d %s\n", elapsed_ms(sim), c->id, msg);
	pthread_mutex_unlock(&sim->print_mutex);
}

void	log_burnout(t_sim *sim, int id)
{
	pthread_mutex_lock(&sim->print_mutex);
	set_stopped(sim);
	printf("%ld %d burned out\n", elapsed_ms(sim), id);
	pthread_mutex_unlock(&sim->print_mutex);
}

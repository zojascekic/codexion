/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zscekic <zscekic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:01:59 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/27 11:39:57 by zscekic          ###   ########.fr       */
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

void	log_take_and_compile(t_coder *c)
{
	t_sim	*sim;
	long	t;

	sim = c->sim;
	pthread_mutex_lock(&sim->print_mutex);
	if (!is_stopped(sim))
	{
		t = elapsed_ms(sim);
		printf("%ld %d has taken a dongle\n", t, c->id);
		printf("%ld %d has taken a dongle\n", t, c->id);
		printf("%ld %d is compiling\n", t, c->id);
	}
	pthread_mutex_unlock(&sim->print_mutex);
}

void	log_burnout(t_sim *sim, int id)
{
	pthread_mutex_lock(&sim->print_mutex);
	set_stopped(sim);
	printf("%ld %d burned out\n", elapsed_ms(sim), id);
	pthread_mutex_unlock(&sim->print_mutex);
}

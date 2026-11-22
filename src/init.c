/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:01:55 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/22 14:01:56 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** init.c  (4/5 functions, init_dongles comes on Day 2 with the heap)
**
**   int          init_sim(t_sim *sim, t_params *p)
**   static int   alloc_coders(t_sim *sim)
**   static int   alloc_dongles(t_sim *sim)
**   static void  link_coder(t_sim *sim, int i)
**   (Day 2)      init_dongles: heap_init for each dongle
*/

static int	alloc_coders(t_sim *sim)
{
	size_t	size;

	size = sizeof(t_coder) * sim->p.n_coders;
	sim->coders = malloc(size);
	if (!sim->coders)
		return (0);
	memset(sim->coders, 0, size);
	return (1);
}

static int	alloc_dongles(t_sim *sim)
{
	size_t	size;

	sim->n_dongles = sim->p.n_coders;
	size = sizeof(t_dongle) * sim->n_dongles;
	sim->dongles = malloc(size);
	if (!sim->dongles)
		return (0);
	memset(sim->dongles, 0, size);
	return (1);
}

/*
** Coder i (0-based) sits between dongle i and dongle (i + 1) % n.
** first = the dongle with the LOWER index, so everybody grabs in the
** same global order -> no circular wait -> no deadlock (Day 3).
** With 1 coder both are dongle 0 (only one dongle on the table).
*/
static void	link_coder(t_sim *sim, int i)
{
	t_coder	*c;
	int		left;
	int		right;

	c = &sim->coders[i];
	c->id = i + 1;
	c->sim = sim;
	c->last_compile = sim->start_time;
	left = i;
	right = (i + 1) % sim->n_dongles;
	if (left < right)
	{
		c->first = &sim->dongles[left];
		c->second = &sim->dongles[right];
	}
	else
	{
		c->first = &sim->dongles[right];
		c->second = &sim->dongles[left];
	}
}

int	init_sim(t_sim *sim, t_params *p)
{
	int	i;

	memset(sim, 0, sizeof(t_sim));
	sim->p = *p;
	if (!alloc_coders(sim) || !alloc_dongles(sim))
		return (0);
	sim->start_time = get_time_ms();
	i = 0;
	while (i < sim->p.n_coders)
	{
		link_coder(sim, i);
		i++;
	}
	return (1);
}

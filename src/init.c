/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zscekic <zscekic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:01:55 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/27 11:17:22 by zscekic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** init.c  (5/5 functions)
**
**   int          init_sim(t_sim *sim, t_params *p)
**   static int   alloc_coders(t_sim *sim)
**   static int   alloc_dongles(t_sim *sim)
**   static int   init_dongles(t_sim *sim)   one heap (capacity 2) each
**   static void  link_coder(t_sim *sim, int i)
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

static int	init_dongles(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->n_dongles)
	{
		if (!heap_init(&sim->dongles[i].queue, 2))
			return (0);
		i++;
	}
	return (1);
}

/*
** Coder i (0-based) sits between dongle i and dongle (i + 1) % n.
** first = the dongle with the LOWER index: every coder LOCKS the two
** dongle mutexes in this same global order -> no circular wait.
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
	if (!alloc_coders(sim) || !alloc_dongles(sim) || !init_dongles(sim))
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

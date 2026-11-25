/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:02:03 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/25 12:16:00 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** main.c  (2/5 functions)
**
**   static int  run_simulation(t_sim *sim)   start threads, wait for them
**   int         main(int argc, char **argv)
**       parse -> init_sim -> init_sync -> run_simulation -> cleanup
*/

static int	run_simulation(t_sim *sim)
{
	int	created;

	created = start_coders(sim);
	if (created < sim->p.n_coders)
	{
		set_stopped(sim);
		wake_all(sim);
		join_coders(sim, created);
		return (0);
	}
	join_coders(sim, created);
	return (1);
}

int	main(int argc, char **argv)
{
	t_params	p;
	t_sim		sim;
	int			ok;

	if (!parse_args(argc, argv, &p))
		return (1);
	ok = init_sim(&sim, &p) && init_sync(&sim);
	if (ok)
		ok = run_simulation(&sim);
	if (!ok)
		fprintf(stderr, "Error: setup failed\n");
	cleanup(&sim);
	return (!ok);
}

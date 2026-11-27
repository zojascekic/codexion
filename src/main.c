/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zscekic <zscekic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:02:03 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/27 11:17:23 by zscekic          ###   ########.fr       */
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
	int	ok;

	created = start_coders(sim);
	ok = (created == sim->p.n_coders);
	if (ok)
		ok = start_monitor(sim);
	if (!ok)
	{
		set_stopped(sim);
		wake_all(sim);
	}
	join_coders(sim, created);
	if (ok)
		pthread_join(sim->monitor, NULL);
	return (ok);
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

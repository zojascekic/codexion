/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:02:03 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/22 14:02:04 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** main.c  (1/5 functions, run_simulation comes on Day 2)
**
**   int  main(int argc, char **argv)
**       parse -> init_sim -> init_sync -> (run) -> cleanup
*/

int	main(int argc, char **argv)
{
	t_params	p;
	t_sim		sim;
	int			ok;

	if (!parse_args(argc, argv, &p))
		return (1);
	ok = init_sim(&sim, &p) && init_sync(&sim);
	if (!ok)
		fprintf(stderr, "Error: setup failed\n");
	cleanup(&sim);
	return (!ok);
}

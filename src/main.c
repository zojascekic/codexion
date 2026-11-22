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
** main.c  (2/5 functions)
**
**   int  main(int argc, char **argv)
**       -> parse_args -> init_sim -> start threads -> join -> cleanup
**          returns 1 on any error
**   static int  run_simulation(t_sim *sim)
**       -> start coders + monitor, wait for them, return status
*/

int	main(int argc, char **argv)
{
	t_params	p;

	if (!parse_args(argc, argv, &p))
		return (1);
	printf("TEMP coders=%d burnout=%d compile=%d debug=%d\n",
		p.n_coders, p.t_burnout, p.t_compile, p.t_debug);
	printf("TEMP refactor=%d required=%d cooldown=%d sched=%d\n",
		p.t_refactor, p.compiles_required, p.cooldown, p.sched);
	return (0);
}

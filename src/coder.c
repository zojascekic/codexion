/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:01:29 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/25 15:58:31 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** coder.c  (1/5 functions)
**
**   void  *coder_routine(void *arg)   the life of one coder thread
**
** Even coders start 10 ms late, so odd coders get the first tickets:
** coders 1, 3, ... compile together at t=0 instead of forming one long
** line (each coder blocked by the one before it).
*/

void	*coder_routine(void *arg)
{
	t_coder	*c;

	c = (t_coder *)arg;
	if (c->id % 2 == 0)
		precise_sleep(c->sim, 10);
	while (!is_stopped(c->sim))
	{
		if (!take_both(c))
			break ;
		do_compile(c);
		release_both(c);
		do_debug(c);
		do_refactor(c);
	}
	return (NULL);
}

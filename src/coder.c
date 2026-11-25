/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:01:29 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/25 12:16:02 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** coder.c  (1/5 functions)
**
**   void  *coder_routine(void *arg)   the life of one coder thread
**
** 1 coder needs no special case: first == second, so the second
** take waits forever (holder is itself) until the monitor stops us.
*/

void	*coder_routine(void *arg)
{
	t_coder	*c;

	c = (t_coder *)arg;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:01:22 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/25 12:16:04 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** coder_actions.c  (3/5 functions)
**
**   void  do_compile(t_coder *c)    holds both dongles while sleeping
**   void  do_debug(t_coder *c)
**   void  do_refactor(t_coder *c)
*/

void	do_compile(t_coder *c)
{
	set_last_compile(c, get_time_ms());
	log_state(c, "is compiling");
	precise_sleep(c->sim, c->sim->p.t_compile);
	inc_compile_count(c);
}

void	do_debug(t_coder *c)
{
	log_state(c, "is debugging");
	precise_sleep(c->sim, c->sim->p.t_debug);
}

void	do_refactor(t_coder *c)
{
	log_state(c, "is refactoring");
	precise_sleep(c->sim, c->sim->p.t_refactor);
}

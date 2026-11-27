/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zscekic <zscekic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:01:22 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/27 11:38:29 by zscekic          ###   ########.fr       */
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
	log_take_and_compile(c);
	precise_sleep(c->sim, c->sim->p.t_compile);
	inc_compile_count(c);
}

void	do_debug(t_coder *c)
{
	log_state(c, "is debugging");
	release_both(c);
	precise_sleep(c->sim, c->sim->p.t_debug);
}

void	do_refactor(t_coder *c)
{
	log_state(c, "is refactoring");
	precise_sleep(c->sim, c->sim->p.t_refactor);
}

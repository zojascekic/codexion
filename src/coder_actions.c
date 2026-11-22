/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:01:22 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/22 14:01:23 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** coder_actions.c  (3/5 functions)
**
**   int   do_compile(t_coder *c)
**       -> take_both; set_last_compile(now); log 'is compiling'; sleep; inc_compile_count; release_both
**   void  do_debug(t_coder *c)
**       -> log 'is debugging'; precise_sleep(time_to_debug)
**   void  do_refactor(t_coder *c)
**       -> log 'is refactoring'; precise_sleep(time_to_refactor)
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:01:29 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/22 14:01:30 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** coder.c  (3/5 functions)
**
**   void  *coder_routine(void *arg)
**       -> if 1 coder -> single_coder_case; else loop until is_stopped: compile, debug, refactor
**   static void single_coder_case(t_coder *c)
**       -> take the only dongle, log it, wait until stopped (monitor burns them out)
**   static int  coder_cycle(t_coder *c)
**       -> do_compile -> do_debug -> do_refactor; return 0 if stopped
*/

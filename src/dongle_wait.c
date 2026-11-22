/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_wait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:01:35 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/22 14:01:36 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"

/*
** dongle_wait.c  (4/5 functions)
**
**   int   wait_for_dongle(t_dongle *d, t_coder *c)
**       -> loop: while !stopped && !(is_my_turn && free && cooldown_done) wait
**   static int  is_my_turn(t_dongle *d, int id)
**       -> heap_peek(d)->coder_id == id
**   static int  cooldown_done(t_dongle *d, t_sim *sim)
**       -> now >= released_at + dongle_cooldown
**   static void wait_step(t_dongle *d, t_sim *sim)
**       -> cond_timedwait until cooldown end (or short timeout) so stop is noticed
*/

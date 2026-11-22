/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:02:07 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/22 14:02:08 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** monitor.c  (4/5 functions)
**
**   void  *monitor_routine(void *arg)
**       -> loop every ~1ms: check_burnout, all_done; stop_and_wake_all when either is true
**   static int  check_burnout(t_sim *sim)
**       -> for each coder: now - get_last_compile >= time_to_burnout -> set_stopped + log_burnout
**   static int  all_done(t_sim *sim)
**       -> every coder get_compile_count >= compiles_required
**   static void stop_and_wake_all(t_sim *sim)
**       -> set_stopped; lock each dongle, cond_broadcast, unlock
*/

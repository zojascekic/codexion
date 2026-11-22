/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:02:32 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/22 14:02:33 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"

/*
** time.c  (4/5 functions)
**
**   long  get_time_ms(void)
**       -> gettimeofday -> milliseconds
**   long  elapsed_ms(t_sim *sim)
**       -> get_time_ms() - sim->start_time (used in logs)
**   void  precise_sleep(t_sim *sim, long ms)
**       -> loop of short usleep(500) until ms passed OR is_stopped
**   void  ms_to_timespec(long abs_ms, struct timespec *ts)
**       -> absolute time for pthread_cond_timedwait
*/

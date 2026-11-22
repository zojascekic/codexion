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
** time.c  (3/5 functions)
**
**   long  get_time_ms(void)                     wall clock in ms
**   long  elapsed_ms(t_sim *sim)                ms since simulation start
**   void  precise_sleep(t_sim *sim, long ms)    small naps, stops early
**
**   Day 4 adds: ms_to_timespec (for pthread_cond_timedwait)
*/

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}

long	elapsed_ms(t_sim *sim)
{
	return (get_time_ms() - sim->start_time);
}

void	precise_sleep(t_sim *sim, long ms)
{
	long	start;

	start = get_time_ms();
	while (!is_stopped(sim) && get_time_ms() - start < ms)
		usleep(500);
}

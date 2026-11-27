/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zscekic <zscekic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:02:32 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/27 11:17:27 by zscekic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** time.c  (4/5 functions)
**
**   long  get_time_ms(void)                     wall clock in ms
**   long  elapsed_ms(t_sim *sim)                ms since simulation start
**   void  precise_sleep(t_sim *sim, long ms)    small naps, stops early
**   void  ms_to_timespec(long ms, struct timespec *ts)   for timedwait
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

/*
** pthread_cond_timedwait wants an ABSOLUTE wall-clock time
** (same clock as gettimeofday), split into seconds + nanoseconds.
** 1400123 ms -> tv_sec = 1400, tv_nsec = 123 * 1000000
*/
void	ms_to_timespec(long ms, struct timespec *ts)
{
	ts->tv_sec = ms / 1000;
	ts->tv_nsec = (ms % 1000) * 1000000;
}

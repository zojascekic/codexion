/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:00:53 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/22 14:00:58 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/*
** ------------------------------------------------------------------
**  MUTEX MAP  (who protects what)
**
**  sim->stop_mutex     -> sim->stopped
**  sim->print_mutex    -> stdout (one log line at a time)
**  coder->mutex        -> coder->last_compile, coder->compile_count
**  dongle->mutex       -> dongle->holder, released_at, queue, next_seq
**  dongle->cond        -> used with dongle->mutex to sleep / wake waiters
**
**  No lock needed (set before threads start, only read afterwards):
**  sim->p, sim->start_time, coder->id, coder->first / second, coder->sim
** ------------------------------------------------------------------
*/

typedef enum e_sched
{
	FIFO,
	EDF
}	t_sched;

typedef struct s_params
{
	int		n_coders;
	int		t_burnout;
	int		t_compile;
	int		t_debug;
	int		t_refactor;
	int		compiles_required;
	int		cooldown;
	t_sched	sched;
}	t_params;

typedef struct s_request
{
	int		coder_id;
	long	seq;
	long	deadline;
}	t_request;

typedef struct s_heap
{
	t_request	*data;
	int			size;
	int			capacity;
}	t_heap;

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	t_heap			queue;
	int				holder;
	long			released_at;
	long			next_seq;
}	t_dongle;

typedef struct s_coder
{
	int				id;
	pthread_t		thread;
	t_dongle		*first;
	t_dongle		*second;
	pthread_mutex_t	mutex;
	long			last_compile;
	int				compile_count;
	struct s_sim	*sim;
}	t_coder;

typedef struct s_sim
{
	t_params		p;
	t_coder			*coders;
	t_dongle		*dongles;
	int				n_dongles;
	long			start_time;
	int				stopped;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	pthread_t		monitor;
}	t_sim;

/* parsing.c         */
int		parse_args(int argc, char **argv, t_params *p);

/* init.c            */
/* init_sync.c       */
/* threads.c         */
/* cleanup.c         */
/* time.c            */
/* log.c             */
/* state.c           */
/* state_coder.c     */
/* heap.c            */
/* heap_utils.c      */
/* scheduler.c       */
/* dongle.c          */
/* dongle_wait.c     */
/* coder.c           */
/* coder_actions.c   */
/* monitor.c         */

#endif

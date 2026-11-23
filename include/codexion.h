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
**  sim->sync_* receipts (only touched by main thread, before / after)
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
	int				sync_globals;
	int				sync_coders;
	int				sync_dongles;
}	t_sim;

/* parsing.c         */
int			parse_args(int argc, char **argv, t_params *p);

/* init.c            */
int			init_sim(t_sim *sim, t_params *p);

/* init_sync.c       */
int			init_sync(t_sim *sim);

/* threads.c         */
/* cleanup.c         */
void		cleanup(t_sim *sim);

/* time.c            */
long		get_time_ms(void);
long		elapsed_ms(t_sim *sim);
void		precise_sleep(t_sim *sim, long ms);

/* log.c             */
void		log_state(t_coder *c, const char *msg);
void		log_burnout(t_sim *sim, int id);

/* state.c           */
int			is_stopped(t_sim *sim);
void		set_stopped(t_sim *sim);

/* state_coder.c     */
long		get_last_compile(t_coder *c);
void		set_last_compile(t_coder *c, long t);
int			get_compile_count(t_coder *c);
void		inc_compile_count(t_coder *c);

/* heap.c            */
int			heap_init(t_heap *h, int capacity);
int			heap_push(t_heap *h, t_request req, t_sched s);
t_request	heap_pop(t_heap *h, t_sched s);
t_request	*heap_peek(t_heap *h);
void		heap_free(t_heap *h);

/* heap_utils.c      */
void		heap_swap(t_request *a, t_request *b);
void		sift_up(t_heap *h, int i, t_sched s);
void		sift_down(t_heap *h, int i, t_sched s);

/* scheduler.c       */
int			compare_requests(t_request *a, t_request *b, t_sched s);

/* dongle.c          */
/* dongle_wait.c     */
/* coder.c           */
/* coder_actions.c   */
/* monitor.c         */

#endif

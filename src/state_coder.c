/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_coder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:02:22 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/22 14:02:23 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** state_coder.c  (4/5 functions)
**
**   long  get_last_compile(t_coder *c)
**   void  set_last_compile(t_coder *c, long t)
**   int   get_compile_count(t_coder *c)
**   void  inc_compile_count(t_coder *c)
**
** Same pattern as is_stopped: lock, copy / change, unlock.
** Written by the coder, read by the monitor -> c->mutex protects both.
*/

long	get_last_compile(t_coder *c)
{
	long	t;

	pthread_mutex_lock(&c->mutex);
	t = c->last_compile;
	pthread_mutex_unlock(&c->mutex);
	return (t);
}

void	set_last_compile(t_coder *c, long t)
{
	pthread_mutex_lock(&c->mutex);
	c->last_compile = t;
	pthread_mutex_unlock(&c->mutex);
}

int	get_compile_count(t_coder *c)
{
	int	n;

	pthread_mutex_lock(&c->mutex);
	n = c->compile_count;
	pthread_mutex_unlock(&c->mutex);
	return (n);
}

void	inc_compile_count(t_coder *c)
{
	pthread_mutex_lock(&c->mutex);
	c->compile_count++;
	pthread_mutex_unlock(&c->mutex);
}

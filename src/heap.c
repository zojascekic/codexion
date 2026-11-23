/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:01:48 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/22 14:01:49 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** heap.c  (5/5 functions)
**
**   int        heap_init(t_heap *h, int capacity)
**   int        heap_push(t_heap *h, t_request req, t_sched s)
**   t_request  heap_pop(t_heap *h, t_sched s)      (caller: size > 0)
**   t_request  *heap_peek(t_heap *h)               NULL if empty
**   void       heap_free(t_heap *h)
**
** Capacity 2 per dongle is enough: only its two neighbours can ever
** wait for it, and each coder has at most one request in the line.
*/

int	heap_init(t_heap *h, int capacity)
{
	h->data = malloc(sizeof(t_request) * capacity);
	if (!h->data)
		return (0);
	h->size = 0;
	h->capacity = capacity;
	return (1);
}

int	heap_push(t_heap *h, t_request req, t_sched s)
{
	if (h->size >= h->capacity)
		return (0);
	h->data[h->size] = req;
	h->size++;
	sift_up(h, h->size - 1, s);
	return (1);
}

t_request	heap_pop(t_heap *h, t_sched s)
{
	t_request	top;

	top = h->data[0];
	h->size--;
	h->data[0] = h->data[h->size];
	sift_down(h, 0, s);
	return (top);
}

t_request	*heap_peek(t_heap *h)
{
	if (h->size == 0)
		return (NULL);
	return (&h->data[0]);
}

void	heap_free(t_heap *h)
{
	free(h->data);
	h->data = NULL;
	h->size = 0;
	h->capacity = 0;
}

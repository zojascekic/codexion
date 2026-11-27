/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zscekic <zscekic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:01:43 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/27 11:17:17 by zscekic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** heap_utils.c  (3/5 functions)
**
**   void  heap_swap(t_request *a, t_request *b)
**   void  sift_up(t_heap *h, int i, t_sched s)     bubble up (push)
**   void  sift_down(t_heap *h, int i, t_sched s)   sink down (pop)
**
** Array math:  parent = (i - 1) / 2   children = 2i + 1, 2i + 2
** "a goes first" = compare_requests(a, b, s) < 0   (scheduler.c)
*/

void	heap_swap(t_request *a, t_request *b)
{
	t_request	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sift_up(t_heap *h, int i, t_sched s)
{
	int	parent;

	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (compare_requests(&h->data[i], &h->data[parent], s) >= 0)
			return ;
		heap_swap(&h->data[i], &h->data[parent]);
		i = parent;
	}
}

void	sift_down(t_heap *h, int i, t_sched s)
{
	int	best;
	int	child;

	while (1)
	{
		best = i;
		child = 2 * i + 1;
		if (child < h->size
			&& compare_requests(&h->data[child], &h->data[best], s) < 0)
			best = child;
		child = 2 * i + 2;
		if (child < h->size
			&& compare_requests(&h->data[child], &h->data[best], s) < 0)
			best = child;
		if (best == i)
			return ;
		heap_swap(&h->data[i], &h->data[best]);
		i = best;
	}
}

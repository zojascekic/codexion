/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:01:43 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/22 14:01:44 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** heap_utils.c  (4/5 functions)
**
**   void  heap_swap(t_request *a, t_request *b)
**       -> swap two entries
**   void  sift_up(t_heap *h, int i, t_sched s)
**       -> while parent is 'after' i (compare_requests) -> swap, go up
**   void  sift_down(t_heap *h, int i, t_sched s)
**       -> swap with best child while child is 'before' i
**   int   heap_remove_id(t_heap *h, int coder_id, t_sched s)
**       -> remove a coder's request (needed if not popped on take)
*/

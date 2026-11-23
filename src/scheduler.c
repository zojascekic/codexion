/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:02:15 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/22 14:02:16 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** scheduler.c  (3/5 functions)
**
**   int         compare_requests(t_request *a, t_request *b, t_sched s)
**   static int  compare_fifo(t_request *a, t_request *b)
**   static int  compare_edf(t_request *a, t_request *b)
**
** Answer to "does a go before b?":  < 0 yes,  > 0 no.
** FIFO: smaller seq first.  EDF: smaller deadline, tie -> smaller seq.
*/

static int	compare_fifo(t_request *a, t_request *b)
{
	if (a->seq < b->seq)
		return (-1);
	if (a->seq > b->seq)
		return (1);
	return (0);
}

static int	compare_edf(t_request *a, t_request *b)
{
	if (a->deadline < b->deadline)
		return (-1);
	if (a->deadline > b->deadline)
		return (1);
	if (a->seq < b->seq)
		return (-1);
	if (a->seq > b->seq)
		return (1);
	return (0);
}

int	compare_requests(t_request *a, t_request *b, t_sched s)
{
	if (s == EDF)
		return (compare_edf(a, b));
	return (compare_fifo(a, b));
}

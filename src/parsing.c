/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:02:11 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/22 14:02:12 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"

/*
** parsing.c  (5/5 functions)
**
**   int  parse_args(int argc, char **argv, t_params *p)
**       -> argc must be 9; parse all 8 args into p; print error to stderr on fail
**   static int  is_valid_number(const char *s)
**       -> optional '+', then digits only, at least one digit
**   static int  str_to_int(const char *s, int *out)
**       -> convert digit by digit, return 0 if > INT_MAX
**   static int  parse_scheduler(const char *s, t_sched *out)
**       -> strcmp with "fifo" / "edf" -> enum, else error
**   static int  check_ranges(t_params *p)
**       -> coders >= 1, compiles_required >= 1, times >= 0
*/

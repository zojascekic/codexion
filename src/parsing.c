/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zscekic <zscekic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:02:11 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/27 11:17:24 by zscekic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** parsing.c  (5/5 functions)
**
**   static int  parse_error(const char *msg)       print "Error: msg", return 0
**   static int  str_to_int(const char *s, int *out) check + convert one number
**   static int  parse_scheduler(const char *s, t_sched *out)  fifo / edf
**   static int  check_ranges(t_params *p)          values that make no sense
**   int         parse_args(int argc, char **argv, t_params *p)
*/

static int	parse_error(const char *msg)
{
	fprintf(stderr, "Error: %s\n", msg);
	return (0);
}

static int	str_to_int(const char *s, int *out)
{
	long	n;
	int		i;

	i = 0;
	if (s[i] == '+')
		i++;
	if (s[i] == '\0')
		return (0);
	n = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		n = n * 10 + (s[i] - '0');
		if (n > INT_MAX)
			return (0);
		i++;
	}
	if (s[i] != '\0')
		return (0);
	*out = (int)n;
	return (1);
}

static int	parse_scheduler(const char *s, t_sched *out)
{
	if (strcmp(s, "fifo") == 0)
		*out = FIFO;
	else if (strcmp(s, "edf") == 0)
		*out = EDF;
	else
		return (0);
	return (1);
}

static int	check_ranges(t_params *p)
{
	if (p->n_coders < 1)
		return (parse_error("number_of_coders must be at least 1"));
	if (p->compiles_required < 1)
		return (parse_error("number_of_compiles_required must be >= 1"));
	return (1);
}

int	parse_args(int argc, char **argv, t_params *p)
{
	int	*fields[7];
	int	i;

	if (argc != 9)
		return (parse_error("expected 8 arguments"));
	fields[0] = &p->n_coders;
	fields[1] = &p->t_burnout;
	fields[2] = &p->t_compile;
	fields[3] = &p->t_debug;
	fields[4] = &p->t_refactor;
	fields[5] = &p->compiles_required;
	fields[6] = &p->cooldown;
	i = 0;
	while (i < 7)
	{
		if (!str_to_int(argv[i + 1], fields[i]))
			return (parse_error("numbers must be integers from 0 to INT_MAX"));
		i++;
	}
	if (!parse_scheduler(argv[8], &p->sched))
		return (parse_error("scheduler must be exactly \"fifo\" or \"edf\""));
	return (check_ranges(p));
}

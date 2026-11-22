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
**       -> read under c->mutex
**   void  set_last_compile(t_coder *c, long t)
**       -> write under c->mutex (at compile START)
**   int   get_compile_count(t_coder *c)
**       -> read under c->mutex
**   void  inc_compile_count(t_coder *c)
**       -> ++ under c->mutex
*/

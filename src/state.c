/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zoja <Zoja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:02:25 by Zoja              #+#    #+#             */
/*   Updated: 2026/11/22 14:02:26 by Zoja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"

/*
** state.c  (2/5 functions)
**
**   int   is_stopped(t_sim *sim)
**       -> lock stop_mutex, read flag, unlock
**   void  set_stopped(t_sim *sim)
**       -> lock stop_mutex, flag = 1, unlock
*/

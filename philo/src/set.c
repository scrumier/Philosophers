/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:26:06 by scrumier          #+#    #+#             */
/*   Updated: 2024/04/29 18:28:18 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_bool(t_mtx *mtx, bool *var, bool value)
{
	pthread_mutex_lock(mtx);
	*var = value;
	pthread_mutex_unlock(mtx);
}

void	set_long(t_mtx *mtx, long *var, long value)
{
	pthread_mutex_lock(mtx);
	*var = value;
	pthread_mutex_unlock(mtx);
}

void	set_int(t_mtx *mtx, int *var, int value)
{
	pthread_mutex_lock(mtx);
	*var = value;
	pthread_mutex_unlock(mtx);
}

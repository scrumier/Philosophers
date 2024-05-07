/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:52:52 by sonamcrumie       #+#    #+#             */
/*   Updated: 2024/04/29 18:12:57 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	get_bool(t_mtx *mtx, bool *var)
{
	bool	value;

	pthread_mutex_lock(mtx);
	value = *var;
	pthread_mutex_unlock(mtx);
	return (value);
}

long	get_long(t_mtx *mtx, long *var)
{
	long	value;

	pthread_mutex_lock(mtx);
	value = *var;
	pthread_mutex_unlock(mtx);
	return (value);
}

int	get_int(t_mtx *mtx, int *var)
{
	int	value;

	pthread_mutex_lock(mtx);
	value = *var;
	pthread_mutex_unlock(mtx);
	return (value);
}

bool	eat_finished(t_table *table)
{
	return (get_bool(&table->table_mtx, &table->end_eat));
}

void	increase_long(t_mtx *mtx, long *var, long value)
{
	pthread_mutex_lock(mtx);
	*var += value;
	pthread_mutex_unlock(mtx);
}

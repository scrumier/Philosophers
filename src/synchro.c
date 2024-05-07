/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:27:32 by sonamcrumie       #+#    #+#             */
/*   Updated: 2024/04/29 17:19:34 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_thread(t_table *table)
{
	while (!get_bool(&table->table_mtx, &table->thread_ready))
		ft_usleep(2, table);
}

bool	all_threads_running(t_mtx *philo,t_mtx *mtx, long *threads, long philo_nbr)
{
	bool	var;

	var = false;
	pthread_mutex_lock(mtx);
	pthread_mutex_lock(philo);
	if (*threads == philo_nbr)
		var = true;
	pthread_mutex_unlock(philo);
	pthread_mutex_unlock(mtx);
	return (var);
}

void	de_synchro(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			ft_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2)
			write_message(philo, "is thinking");
	}
}

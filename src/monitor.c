/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:13:44 by sonamcrumie       #+#    #+#             */
/*   Updated: 2024/04/30 13:48:26 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	philo_die(t_philo *philo, long time_to_die)
{
	long	time;

	if (get_bool(&philo->philo_mtx, &philo->full))
		return (false);
	time = gettime(MILLISECONDS) - \
		get_long(&philo->philo_mtx, &philo->last_ate);
	if (time > time_to_die *0.001)
		return (true);
	return (false);
}

static bool all_full(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (!get_bool(&table->philos[i].philo_mtx, &table->philos[i].full))
			return (false);
		i++;
	}
	return (true);
}

void	*monitor_handler(void *arg)
{
	t_table	*table;
	int		i;
	long	time_to_die;

	time_to_die = ((t_table *)arg)->time_to_die;
	table = (t_table *)arg;
	while (!all_threads_running(&table->philos->philo_mtx, &table->table_mtx, \
			&table->threads_running, table->philo_nbr))
		;
	while (!eat_finished(table))
	{
		i = 0;
		while (i < table->philo_nbr)
		{
			if (philo_die(table->philos + i, time_to_die) && !eat_finished(table))
			{
				set_bool(&table->table_mtx, &table->end_eat, true);
				pthread_mutex_lock(&table->write_mtx);
				printf("%ld %d died\n", gettime(MILLISECONDS) - \
					table->start, table->philos[i].id);
				pthread_mutex_unlock(&table->write_mtx);
			}
			i++;
		}
			if (table->nb_eat > 0 && all_full(table))
			{
				set_bool(&table->table_mtx, &table->end_eat, true);
				break ;
			}
	}
	return (NULL);
}

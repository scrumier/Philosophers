/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:03:23 by sonamcrumie       #+#    #+#             */
/*   Updated: 2024/05/21 14:38:58 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	take_fork(t_mtx *mtx, bool *taken)
{
	bool	ret;

	ret = 0;
	pthread_mutex_lock(mtx);
	if (!*taken)
	{
		ret = 1;
		*taken = 1;
	}
	pthread_mutex_unlock(mtx);
	return (ret);
}

static void	can_i_take_fork(t_philo *philo)
{
	int	left;
	int	right;

	left = 0;
	right = 0;
	while (!eat_finished(philo->table))
	{
		if (!left)
			left = take_fork(&philo->first_fork->fork, \
					&philo->first_fork->taken);
		if (!right)
			right = take_fork(&philo->second_fork->fork, \
					&philo->second_fork->taken);
		if (left && right)
			break ;
		usleep(10);
	}
}

static void	eat(t_philo *philo, long time_to_eat)
{
	struct timeval	now;
	long			now_milli;

	can_i_take_fork(philo);
	write_message(philo, "has taken a fork");
	write_message(philo, "has taken a fork");
	gettimeofday(&now, NULL);
	now_milli = now.tv_sec * 1e3 + now.tv_usec * 0.001;
	set_long(&philo->philo_mtx, &philo->last_ate, now_milli);
	increase_long(&philo->table->table_mtx, &philo->time_eaten, 1);
	write_message(philo, "is eating");
	ft_usleep(time_to_eat, philo->table);
	if (philo->table->nb_eat > 0 && philo->time_eaten == philo->table->nb_eat)
		set_bool(&philo->philo_mtx, &philo->full, true);
	set_bool(&philo->first_fork->fork, &philo->first_fork->taken, 0);
	set_bool(&philo->second_fork->fork, &philo->second_fork->taken, 0);
}

static void	*routine(void *data)
{
	t_philo			*philo;
	long			sleep_time;
	long			eat_time;
	struct timeval	now;
	long			now_milli;

	philo = (t_philo *)data;
	eat_time = philo->table->time_to_eat;
	sleep_time = philo->table->time_to_sleep;
	wait_thread(philo->table);
	gettimeofday(&now, NULL);
	now_milli = now.tv_sec * 1e3 + now.tv_usec * 0.001;
	set_long(&philo->philo_mtx, &philo->last_ate, now_milli);
	increase_long(&philo->table->table_mtx, &philo->table->threads_running, 1);
	de_synchro(philo);
	while (!eat_finished(philo->table))
	{
		eat(philo, eat_time);
		write_message(philo, "is sleeping");
		ft_usleep(sleep_time, philo->table);
		write_message(philo, "is thinking");
	}
	return (NULL);
}

void	dinner(t_table *table)
{
	int	i;

	i = -1;
	table->start = gettime(MILLISECONDS);
	if (table->nb_eat == 0)
		return ;
	else if (table->philo_nbr == 1)
	{
		pthread_create(&table->philos[0].thread_id, NULL, one_philo, \
			&table->philos[0]);
	}
	else
	{
		while (++i < table->philo_nbr)
			pthread_create(&table->philos[i].thread_id, \
				NULL, routine, &table->philos[i]);
	}
	pthread_create(&table->monitor, NULL, monitor_handler, table);
	i = -1;
	set_bool(&table->table_mtx, &table->thread_ready, true);
	while (++i < table->philo_nbr)
		pthread_join(table->philos[i].thread_id, NULL);
	set_bool(&table->table_mtx, &table->end_eat, true);
	pthread_join(table->monitor, NULL);
}

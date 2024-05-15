/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:03:23 by sonamcrumie       #+#    #+#             */
/*   Updated: 2024/05/15 15:30:01 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	release_forks(t_philo *philo)
{
	if (get_bool(&philo->first_fork->fork, &philo->first_fork->taken))
	{
		pthread_mutex_unlock(&philo->first_fork->fork);
		set_bool(&philo->first_fork->fork, &philo->first_fork->taken, false);
	}
	if (get_bool(&philo->second_fork->fork, &philo->second_fork->taken))
	{
		pthread_mutex_unlock(&philo->second_fork->fork);
		set_bool(&philo->second_fork->fork, &philo->second_fork->taken, false);
	}
}

static void	can_i_take_fork(t_philo *philo)
{
	while (!eat_finished(philo->table))
	{
		if (!get_bool(&philo->first_fork->fork, &philo->first_fork->taken) && \
			!get_bool(&philo->second_fork->fork, &philo->second_fork->taken))
		{
			set_bool(&philo->first_fork->fork, \
					&philo->first_fork->taken, true);
			pthread_mutex_lock(&philo->first_fork->fork);
			set_bool(&philo->second_fork->fork, \
					&philo->second_fork->taken, true);
			pthread_mutex_lock(&philo->second_fork->fork);
			break ;
		}
		else
		{
			release_forks(philo);
		}
		usleep(100);
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
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
	set_bool(&philo->first_fork->fork, &philo->first_fork->taken, false);
	set_bool(&philo->second_fork->fork, &philo->second_fork->taken, false);
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
	table->start = gettime(MILLISECONDS);
	i = -1;
	set_bool(&table->table_mtx, &table->thread_ready, true);
	while (++i < table->philo_nbr)
		pthread_join(table->philos[i].thread_id, NULL);
	set_bool(&table->table_mtx, &table->end_eat, true);
	pthread_join(table->monitor, NULL);
}

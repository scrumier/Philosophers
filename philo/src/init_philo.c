/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:38:07 by scrumier          #+#    #+#             */
/*   Updated: 2024/07/10 05:42:51 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	assign_forks(t_philo *philo, t_fork *forks, int i)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->first_fork = &forks[(i + 1) % philo_nbr];
	philo->second_fork = &forks[i];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[i];
		philo->second_fork = &forks[(i + 1) % philo_nbr];
	}
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->time_eaten = 0;
		pthread_mutex_init(&philo->philo_mtx, NULL);
		philo->table = table;
		assign_forks(philo, table->forks, i);
		i++;
	}
	i = 0;
	while (i < table->philo_nbr)
	{
		table->forks[i].taken = false;
		i++;
	}
}

int	data_init(t_table *table)
{
	int	i;

	i = 0;
	table->end_eat = false;
	table->thread_ready = false;
	table->threads_running = 0;
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = malloc(sizeof(t_fork) * table->philo_nbr);
	pthread_mutex_init(&table->write_mtx, NULL);
	pthread_mutex_init(&table->table_mtx, NULL);
	if (!table->forks || !table->philos)
		return (clean(table), ft_failure(FAIL_MALLOC));
	while (i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
			return (ft_failure(FAIL_MUTEX_INIT));
		table->forks[i].id = i;
		i++;
	}
	philo_init(table);
	return (EXIT_SUCCESS);
}

int	ft_init_struct(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		return (ft_failure("Error: time_to_die, time_to_eat and \
			time_to_sleep must be greater than 60ms\n"));
	if (av[5])
		table->nb_eat = ft_atol(av[5]);
	else
		table->nb_eat = -1;
	return (EXIT_SUCCESS);
}

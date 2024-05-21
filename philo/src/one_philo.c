/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:56:13 by sonamcrumie       #+#    #+#             */
/*   Updated: 2024/05/21 14:55:52 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_thread(philo->table);
	set_long(&philo->philo_mtx, &philo->last_ate, gettime(MILLISECONDS) - \
		philo->table->start);
	increase_long(&philo->table->table_mtx, &philo->table->threads_running, 1);
	write_message(philo, "take a fork");
	ft_usleep(philo->table->time_to_die, philo->table);
	printf("%ld %d %s\n", philo->table->time_to_die / 1000, \
			get_int(&philo->philo_mtx, &philo->id), "died");
	set_bool(&philo->table->table_mtx, &philo->table->end_eat, true);
	return (NULL);
}

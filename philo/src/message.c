/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:23:36 by sonamcrumie       #+#    #+#             */
/*   Updated: 2024/05/21 14:48:46 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	write_message(t_philo *philo, char *message)
{
	struct timeval	now;
	long			time;
	int				ret;

	pthread_mutex_lock(&philo->table->table_mtx);
	gettimeofday(&now, NULL);
	time = now.tv_sec * 1e3 + now.tv_usec / 1e3 - philo->table->start;
	pthread_mutex_unlock(&philo->table->table_mtx);
	pthread_mutex_lock(&philo->table->write_mtx);
	if (!get_bool(&philo->table->table_mtx, &philo->table->end_eat))
		ret = printf("%ld %d %s\n", time, \
			get_int(&philo->philo_mtx, &philo->id), message);
	pthread_mutex_unlock(&philo->table->write_mtx);
}

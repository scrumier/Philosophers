/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:53:13 by scrumier          #+#    #+#             */
/*   Updated: 2024/05/21 14:46:04 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

int	ft_isnbr(char *c)
{
	int	i;

	i = 0;
	while (c[i] != '\0')
	{
		if (c[i] < '0' || c[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

long	gettime(t_timecode timecode)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	else if (timecode == MILLISECONDS)
		return (tv.tv_sec * 1e3 + tv.tv_usec * 0.001);
	else if (timecode == MICROSECONDS)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	return (-42000);
}

void	clean(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->forks[i].fork);
		pthread_mutex_destroy(&table->philos[i].philo_mtx);
		i++;
	}
	pthread_mutex_destroy(&table->write_mtx);
	pthread_mutex_destroy(&table->table_mtx);
	free(table->forks);
	free(table->philos);
}

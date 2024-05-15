/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:25:44 by scrumier          #+#    #+#             */
/*   Updated: 2024/05/15 15:25:51 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_until(long start_micro, long time)
{
	struct timeval	current;
	long			current_micro;

	while (42)
	{
		gettimeofday(&current, NULL);
		current_micro = current.tv_sec * 1e6 + current.tv_usec;
		if (current_micro - start_micro >= time)
			break ;
	}
}

void	ft_usleep(long time, t_table *table)
{
	struct timeval	current;
	long			elapsed;
	long			remaining;
	long			start_micro;
	long			current_micro;

	gettimeofday(&current, NULL);
	start_micro = current.tv_sec * 1e6 + current.tv_usec;
	while (42)
	{
		gettimeofday(&current, NULL);
		current_micro = current.tv_sec * 1e6 + current.tv_usec;
		elapsed = current_micro - start_micro;
		if (elapsed >= time || eat_finished(table))
			break ;
		remaining = time - elapsed;
		if (remaining > 1e4)
			usleep(remaining * 0.5);
		else
			wait_until(start_micro, time);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:28:06 by scrumier          #+#    #+#             */
/*   Updated: 2024/04/29 18:15:26 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ft_check_args(ac, av) == EXIT_SUCCESS && ft_atol(av[1]))
	{
		if (ft_init_struct(&table, av) == EXIT_FAILURE)
			return (ft_failure("Malloc failed\n"));
		if (data_init(&table) == EXIT_FAILURE)
			return (ft_failure("Malloc failed\n"));
		dinner(&table);
		clean(&table);
	}
	else
	{
		ft_failure("Wrong input:\n"
			"./philo 5 800 200 200 [7]\n"
			"         t_die t_eat t_sleep [meals_limit]\n");
	}
}

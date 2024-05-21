/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:49:18 by scrumier          #+#    #+#             */
/*   Updated: 2024/05/21 14:35:15 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	*ft_skip_spaces(char *str)
{
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	return (str);
}

long	ft_atol(char *str)
{
	long	res;

	res = 0;
	str = ft_skip_spaces(str);
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	if (res > 2147483647)
		return (-1);
	return (res);
}

int	ft_check_args(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (ft_failure(BAD_AC));
	while (av[i])
	{
		if (ft_isnbr(av[i]) == 1)
			return (ft_failure(BAD_AV));
		if (ft_strlen(av[i]) > 10)
			return (ft_failure(BAD_AV));
		i++;
	}
	if (ft_atol(av[1]) < 1 || ft_atol(av[1]) > 200)
		return (ft_failure(BAD_NBR_PHILO));
	if (ft_atol(av[2]) < 1 || ft_atol(av[3]) < 1 || ft_atol(av[4]) < 1)
		return (ft_failure(BAD_AV));
	if (ac == 6 && ft_atol(av[5]) < 1)
		return (ft_failure(BAD_NBR_EAT));
	return (EXIT_SUCCESS);
}

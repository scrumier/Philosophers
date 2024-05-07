/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:15:35 by scrumier          #+#    #+#             */
/*   Updated: 2024/04/29 16:44:09 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_failure(char *str)
{
	printf("%s", str);
	return (EXIT_FAILURE);
}

int	ft_succes(char *str)
{
	printf("%s", str);
	return (EXIT_SUCCESS);
}

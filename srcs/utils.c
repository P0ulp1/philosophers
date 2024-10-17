/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:14:38 by phautena          #+#    #+#             */
/*   Updated: 2024/10/17 14:51:09 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	neg;

	i = 0;
	result = 0;
	neg = 1;
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == ' ')
	{
		i++;
	}
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg *= -1;
		i++;
	}
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * neg);
}

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
//THIS IS SHIT//
// size_t	get_current_time(void)
// {
// 	struct timeval	time;

// 	if (gettimeofday(&time, NULL) == -1)
// 		return (printf("Error from gettimeofday()\n"));
// 	return (time.tv_sec / 1000);
// }

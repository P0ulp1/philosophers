/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:55:28 by phautena          #+#    #+#             */
/*   Updated: 2024/10/18 11:23:13 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	t_program		data;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (argc < 5 || argc > 6)
		return (printf("[-] Usage: ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [philos_eat_n_times]"));
	if (check_args(argv))
		return (1);
	init_data(&data, philos);
	init_forks(forks, ft_atoi(argv[1]));
	init_philos(philos, &data, forks, argv);
	create_threads(&data, forks);
	return (0);
}

int	check_args(char *argv[])
{
	if (ft_atoi(argv[1]) > 200 || ft_isnum(argv[1]) || ft_atoi(argv[1]) <= 0)
		return (printf("Invalid number of philosophers\n"));
	if (ft_isnum(argv[2]) || ft_atoi(argv[2]) <= 0)
		return (printf("Invalid time to die\n"));
	if (ft_isnum(argv[3]) || ft_atoi(argv[3]) <= 0)
		return (printf("Invalid time to eat\n"));
	if (ft_isnum(argv[4]) || ft_atoi(argv[4]) <= 0)
		return (printf("Invalid time to sleep"));
	if (argv[5])
	{
		if (ft_isnum(argv[5]) || ft_atoi(argv[5]) <= 0)
			return (printf("Invalid number of times a philosopher must eat\n"));
	}
	return (0);
}

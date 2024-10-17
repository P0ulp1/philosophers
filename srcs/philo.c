/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:55:28 by phautena          #+#    #+#             */
/*   Updated: 2024/10/17 14:23:57 by phautena         ###   ########.fr       */
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
	printf("Time: %zu\n", get_current_time());
	return (0);
}

void	init_philos(t_philo *philos, char *argv[])
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philos->id = i + 1;
		philos->eating = 0;
		philos->meals_eaten = 0;
		//Set input values (time to die; time to eat; time to sleep; n_philo)
		// philos->start_time = gettimeofday()
	}
}

void	init_forks(pthread_mutex_t *forks, int n_philo)
{
	int	i;

	i = 0;
	while (i < n_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_data(t_program *data, t_philo *philos)
{
	data->dead_flag = 0;
	data->philos = philos;
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
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

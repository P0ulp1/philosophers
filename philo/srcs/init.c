/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:41:35 by phautena          #+#    #+#             */
/*   Updated: 2024/10/29 13:52:51 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].must_eat_n = 0;
		data->philos[i].data = data;
		data->philos[i].first_fork = &data->forks[i];
		data->philos[i].second_fork = &data->forks[(i + 1) % data->nb_philo];
	}
}

static int	init_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (printf("Error while initializing forks mutexes\n"));
	}
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (printf("Error while initializing write_lock mutex\n"));
	if (pthread_mutex_init(&data->must_eat_lock, NULL) != 0)
		return (printf("Error while initializing must_eat_lock mutex\n"));
	return (0);
}

static int	parse_argv(t_data *data, char *argv[])
{
	data->nb_philo = ft_atoi(argv[1]);
	data->tt_die = ft_atoi(argv[2]);
	data->tt_eat = ft_atoi(argv[3]);
	data->tt_sleep = ft_atoi(argv[4]);
	if (data->nb_philo == -1 || data->tt_die == -1
		|| data->tt_eat == -1 || data->tt_sleep == -1)
		return (printf("Arguments are invalid\n"));
	if (argv[5])
	{
		data->must_eat = ft_atoi(argv[5]);
		if (data->must_eat == -1)
			return (printf("Arguments are invalid\n"));
	}
	else
		data->must_eat = -1;
	if (data->nb_philo < 1 || data->nb_philo > 200)
		return (printf("Incorrect number of philos\n"));
	if (data->tt_die < 60 || data->tt_eat < 60 || data->tt_sleep < 60)
		return (printf("Please do not use time < 60ms\n"));
	return (0);
}

static int	init_data(t_data *data, char *argv[])
{
	if (parse_argv(data, argv) != 0)
		return (1);
	data->end = false;
	data->start = false;
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (printf("Error while allocating memory for philos\n"));
	data->forks = malloc(sizeof(t_mtx) * data->nb_philo);
	if (!data->forks)
		return (printf("Error while allocating memory for forks\n"));
	if (init_mutexes(data) != 0)
		return (2);
	return (0);
}

int	init_all(t_data *data, char *argv[])
{
	if (init_data(data, argv) != 0)
		return (1);
	init_philos(data);
	return (0);
}

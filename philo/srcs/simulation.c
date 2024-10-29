/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:26:27 by phautena          #+#    #+#             */
/*   Updated: 2024/10/29 13:51:31 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_all_ate(t_data *data)
{
	int	i;
	int	ate;

	i = -1;
	ate = 0;
	pthread_mutex_lock(&data->must_eat_lock);
	while (++i < data->nb_philo)
	{
		if (data->philos[i].must_eat_n == data->must_eat)
			ate++;
	}
	pthread_mutex_unlock(&data->must_eat_lock);
	if (ate == data->nb_philo)
		return (true);
	return (false);
}

static void	monitor(t_data *data)
{
	int	i;

	precise_sleep(60);
	while (data->end == false)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			if (get_time() - data->philos[i].last_meal > data->tt_die)
			{
				safe_write(&data->philos[i], "has died");
				data->end = true;
				break ;
			}
		}
		if (data->end == true)
			break ;
		if (check_all_ate(data) == true)
		{
			data->end = true;
			break ;
		}
	}
}

static void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->end == false)
	{
		pthread_mutex_lock(philo->first_fork);
		safe_write(philo, "has taken a fork");
		pthread_mutex_lock(philo->second_fork);
		safe_write(philo, "has taken a fork");
		philo->last_meal = get_time();
		pthread_mutex_lock(&data->must_eat_lock);
		philo->must_eat_n += 1;
		pthread_mutex_unlock(&data->must_eat_lock);
		safe_write(philo, "is eating");
		precise_sleep(data->tt_eat);
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
	}
}

static void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (data->start == false)
		;
	philo->last_meal = get_time();
	if (data->nb_philo == 1)
	{
		lone_philo(data);
		return (NULL);
	}
	if (philo->id % 2)
		precise_sleep(60);
	while (data->end == false)
	{
		philo_eat(philo);
		safe_write(philo, "is sleeping");
		precise_sleep(data->tt_sleep);
		safe_write(philo, "is thinking");
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]) != 0)
			return (printf("Error while creating a thread\n"));
	}
	data->start_time = get_time();
	data->start = true;
	monitor(data);
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (printf("Error while joining a thread\n"));
	}
	return (0);
}

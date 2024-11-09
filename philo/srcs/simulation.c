/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:26:27 by phautena          #+#    #+#             */
/*   Updated: 2024/11/09 15:30:14 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_all_ate(t_data *data)
{
	int	i;
	int	ate;

	i = -1;
	ate = 0;
	while (++i < data->nb_philo)
	{
		pthread_mutex_lock(&data->must_eat_lock);
		if (data->philos[i].must_eat_n >= data->must_eat)
			ate++;
		pthread_mutex_unlock(&data->must_eat_lock);
	}
	if (ate == data->nb_philo)
		return (true);
	return (false);
}

static void	monitor(t_data *data)
{
	int		i;
	long	last_meal;

	precise_sleep(60);
	while (data->end == false)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			last_meal = get_long(&data->time_lock, &data->philos[i].last_meal);
			if (get_time() - last_meal > data->tt_die)
			{
				safe_write(&data->philos[i], "died");
				set_bool(&data->end_lock, &data->end, true);
				break ;
			}
		}
		if (data->end == true)
			break ;
		if (data->must_eat != -1 && check_all_ate(data) == true)
		{
			set_bool(&data->end_lock, &data->end, true);
			break ;
		}
	}
}

static void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (get_bool(&data->end_lock, &data->end) == false)
	{
		pthread_mutex_lock(philo->first_fork);
		safe_write(philo, "has taken a fork");
		pthread_mutex_lock(philo->second_fork);
		safe_write(philo, "has taken a fork");
		set_long(&data->time_lock, &philo->last_meal, get_time());
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
	while (get_bool(&data->start_lock, &data->start) == false)
		;
	set_long(&data->time_lock, &philo->last_meal, get_time());
	if (data->nb_philo == 1)
	{
		lone_philo(data);
		return (NULL);
	}
	if (philo->id % 2)
		precise_sleep(60);
	while (get_bool(&data->end_lock, &data->end) == false)
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
	set_long(&data->time_lock, &data->start_time, get_time());
	set_bool(&data->start_lock, &data->start, true);
	monitor(data);
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (printf("Error while joining a thread\n"));
	}
	return (0);
}

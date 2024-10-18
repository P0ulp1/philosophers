/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:48:07 by phautena          #+#    #+#             */
/*   Updated: 2024/10/18 13:53:26 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	create_threads(t_program *data, pthread_mutex_t *forks)
{
	pthread_t	monitor;
	int			i;

	if (pthread_create(&monitor, NULL, monitor_routine, data->philos) != 0)
		destroy_mutexes(&data, forks);
	i = 0;
	while (i < data->philos[0].n_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine, &data->philos[i]) != 0)
			destroy_mutexes(&data, forks);
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
		destroy_mutexes(&data, forks);
	i = 0;
	while (i < data->philos[0].n_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			destroy_mutexes(&data, forks);
		i++;
	}
	(void)forks;
}

void	*monitor_routine(void *ptr)
{
	(void)ptr;
	return (0);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *) ptr;
	return (0);
}

int	philo_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= philo->time_to_die && philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	return (0);
}

int	dead_loop(t_philo *philo) //Still why?
{
	pthread_mutex_lock(philo->dead_lock);
	if (philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

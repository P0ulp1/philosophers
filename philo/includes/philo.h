/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:25:24 by phautena          #+#    #+#             */
/*   Updated: 2024/10/29 13:52:39 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//includes
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

//defines / typedefs
typedef pthread_mutex_t	t_mtx;
typedef struct s_data	t_data;

//structures
typedef struct s_philo
{
	int			id;
	int			must_eat_n;
	long		last_meal;
	pthread_t	thread;
	t_mtx		*first_fork;
	t_mtx		*second_fork;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	int		nb_philo;
	int		must_eat;
	long	tt_die;
	long	tt_eat;
	long	tt_sleep;
	long	start_time;
	bool	end;
	bool	start;
	t_philo	*philos;
	t_mtx	*forks;
	t_mtx	write_lock;
	t_mtx	must_eat_lock;
}	t_data;

//prototypes
///simulation.c
int		start_simulation(t_data *data);
///init.c
int		init_all(t_data *data, char *argv[]);
///utils.c
long	ft_atoi(const char *nptr);
long	get_time(void);
void	precise_sleep(long usec);
void	safe_write(t_philo *philo, char *status);
void	lone_philo(t_data *data);
///sync_utils.c
bool	get_bool(t_mtx *mutex, bool *value);
void	set_bool(t_mtx *mutex, bool *value, bool to_set);
long	get_long(t_mtx *mutex, long *value);
void	set_long(t_mtx *mutex, long *value, long to_set);

#endif

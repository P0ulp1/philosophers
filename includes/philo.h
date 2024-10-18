/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:08:06 by phautena          #+#    #+#             */
/*   Updated: 2024/10/18 12:10:29 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define PHILO_MAX 200
# define ERROR 1
# define SUCCESS 0

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				n_philo;
	int				n_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}	t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}	t_program;

///philo.c>>>
int		main(int argc, char *argv[]);
int		check_args(char *argv[]);

///init.c>>>
void	init_data(t_program *data, t_philo *philos);
void	init_forks(pthread_mutex_t *forks, int n_philo);
void	init_philos(t_philo *philos, t_program *data, pthread_mutex_t *forks, char *argv[]);
void	set_input(t_philo *philo, char *argv[]);

///threads.c>>>
void	create_threads(t_program *data, pthread_mutex_t *forks);
void	*monitor_routine(void *ptr);
void	*philo_routine(void *ptr);
int		dead_loop(t_philo *philo);

///utils.c>>>
int		ft_atoi(const char *nptr);
int		ft_isnum(char *str);
size_t	get_current_time(void);
void	destroy_mutexes(t_program *data, pthread_mutex_t *forks);
void	print_message(char *str, t_philo *philo);

#endif

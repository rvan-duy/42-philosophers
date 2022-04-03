/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 16:22:31 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/03 12:59:07 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
#include <stdio.h>

typedef struct s_data {
	size_t			num_of_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			max_eat_count;
	long long		start_time;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	extra_lock;
	bool			philo_died;
}	t_data;

typedef struct s_philo {
	size_t			seat;
	size_t			times_eaten;
	useconds_t		time_since_last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

typedef enum e_status {
	SUCCESS,
	FAILURE
}	t_status;

typedef enum e_arguments {
	NUM_OF_PHILO,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	MAX_EAT_COUNT
}	t_arguments;

t_status	start_threads(t_data *data, t_philo *philos);

// routine
void		*routine(void *arg);
void		go_eat(t_philo *philo_data);
void		go_sleep(t_philo *philo_data);
void		go_think(t_philo *philo_data);

// init & destroy
t_status	init_data(t_data *data, int argc, char **argv);
t_status	init_philos(t_data *data, t_philo **philos);
void		destroy_data(t_data *data);
void		destroy_philos(t_philo **philos);

// utils
void		*my_calloc(size_t nmemb, size_t size);
void		protected_print(char *msg, t_philo *philo);
bool		check_end_condition(t_philo *philo_data);

// time
long long	get_time_in_ms(void);
long long	get_timestamp(long long start_timestamp);
void		stupid_sleep(unsigned long time2sleep);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 16:22:31 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/30 20:20:04 by rvan-duy      ########   odam.nl         */
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
	struct timeval	start_time;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
	bool			philo_died;
	pthread_mutex_t	philo_died_lock;
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
int			my_usleep(useconds_t microseconds, t_philo *philo);
void		*my_calloc(size_t nmemb, size_t size);
void		protected_print(char *msg, t_philo *philo);
useconds_t	get_timestamp(t_data *data);
bool		check_for_dead(t_philo *philo_data);

#endif

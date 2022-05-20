/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 16:22:31 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/05/20 13:49:07 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
#   include <stdio.h>

typedef size_t	t_timestamp;

// sleep timers in microseconds
# define ODD_PHILO_WAIT_TIME_BEFORE_START 500
# define SLEEP_INBETWEEN_PHILO_START 250
# define MONITORING_DELAY 250

typedef enum e_state {
	EAT,
	NOT_EAT
}	t_state;

typedef struct s_data {
	size_t			num_of_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			max_eat_count;
	t_timestamp		start_time;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*last_meal_lock;
	pthread_mutex_t	philo_died_lock;
	bool			a_philo_died;
}	t_data;

typedef struct s_philo {
	size_t			seat;
	size_t			times_eaten;
	t_timestamp		last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*last_meal_lock;
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
void		go_eat(t_philo *p);
void		go_sleep(t_philo *p);
void		go_think(t_philo *p);

// init & destroy
t_status	init_data(t_data *data, int argc, char **argv);
t_status	init_philos(t_data *data, t_philo **philos);
void		destroy_data(t_data *data);
void		destroy_philos(t_philo **philos);

// utils
void		*util_calloc(size_t nmemb, size_t size);
size_t		util_strlen(const char *str);
int			util_putstr_fd(const char *s, int fd);
int			util_putchar_fd(const char c, int fd);
void		util_putnbr_fd(size_t n, int fd);

// print
void		print_dead(t_philo *p, const t_timestamp current_time);
bool		is_dead(t_philo *p);
bool		print_message(const char *message, t_philo *p);

// time
t_timestamp	get_time_in_ms(void);
t_timestamp	get_timestamp(const t_timestamp start_time);
void		stupid_sleep(size_t time2sleep);

#endif

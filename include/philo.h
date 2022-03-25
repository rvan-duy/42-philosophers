/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 16:22:31 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/25 17:39:28 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>

typedef struct s_data {
	size_t	number_of_philosophers;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
}	t_data;

typedef enum e_return_status {
	SUCCESS,
	FAILURE
}	t_return_status;

typedef enum e_arguments {
	NUMBER_OF_PHILOSOPHERS,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	MAX_EAT_COUNT
}	t_arguments;

typedef enum e_status {
	EAT,
	SLEEP,
	THINK,
	DEAD
}	t_status;

#endif

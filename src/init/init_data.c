/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 14:11:47 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/30 14:51:03 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static char	*get_argument(t_arguments arg)
{
	char *const	arguments[] = {
		"number_of_philosophers",
		"time_to_die",
		"time_to_eat",
		"time_to_sleep",
		"number_of_times_each_philosopher_must_eat"
	};

	return (arguments[arg]);
}

static t_status	philo_atoi(size_t *num, char *str, t_arguments arg)
{
	int	i;

	*num = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		printf("%s cannot be negative\n", get_argument(arg));
		return (FAILURE);
	}
	if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= 48 && str[i] <= 57)
	{
		*num = *num * 10 + str[i] - 48;
		i++;
	}
	if (*num == 0)
	{
		printf("%s cannot be zero\n", get_argument(arg));
		return (FAILURE);
	}
	return (SUCCESS);
}

// TODO: handle mutex creation failure better
t_status	init_forks(size_t num, pthread_mutex_t **fork_array)
{
	size_t	i;

	*fork_array = my_calloc(num, sizeof(pthread_mutex_t));
	if (*fork_array == NULL)
		return (FAILURE);
	i = 0;
	while (i < num)
	{
		if (pthread_mutex_init(&(*fork_array)[i], NULL) != SUCCESS)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

t_status	init_data(t_data *data, int argc, char **argv)
{
	t_status	status;

	status = SUCCESS;
	if (philo_atoi(&data->num_of_philo, argv[1], NUM_OF_PHILO) == FAILURE)
		status = FAILURE;
	if (philo_atoi(&data->time_to_die, argv[2], TIME_TO_DIE) == FAILURE)
		status = FAILURE;
	if (philo_atoi(&data->time_to_eat, argv[3], TIME_TO_EAT) == FAILURE)
		status = FAILURE;
	if (philo_atoi(&data->time_to_sleep, argv[4], TIME_TO_SLEEP) == FAILURE)
		status = FAILURE;
	if (argc == 6)
	{
		if (philo_atoi(&data->max_eat_count, argv[5], MAX_EAT_COUNT) == FAILURE)
			status = FAILURE;
	}
	if (status == SUCCESS)
	{
		if (init_forks(data->num_of_philo, &data->forks) == FAILURE)
			status = FAILURE;
	}
	return (status);
}

void	destroy_data(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
}
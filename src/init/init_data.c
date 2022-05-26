/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 14:11:47 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/05/26 14:07:57 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static t_status	init_mutex_array(size_t num, pthread_mutex_t **mutex_array)
{
	size_t	i;

	*mutex_array = util_calloc(num, sizeof(pthread_mutex_t));
	if (*mutex_array == NULL)
		return (FAILURE);
	i = 0;
	while (i < num)
	{
		if (pthread_mutex_init(&(*mutex_array)[i], NULL) != SUCCESS)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static t_status	init_mutexes(t_status status, t_data *data)
{
	if (init_mutex_array(data->num_of_philo, &data->forks) == FAILURE)
		status = FAILURE;
	if (init_mutex_array(data->num_of_philo, &data->last_meal_lock) == FAILURE)
		status = FAILURE;
	if (init_mutex_array(data->num_of_philo, \
							&data->times_eaten_lock) == FAILURE)
		status = FAILURE;
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->philo_died_lock, NULL);
	data->a_philo_died = false;
	data->philos_ate_enough = false;
	return (status);
}

static t_status	get_max_eat_count(t_data *data, int argc, char **argv)
{
	t_status	status;

	status = SUCCESS;
	if (argc == 6)
	{
		data->max_eat_count_enabled = true;
		if (util_atoi(&data->max_eat_count, argv[5], MAX_EAT_COUNT) == FAILURE)
			status = FAILURE;
	}
	else
	{
		data->max_eat_count = 0;
		data->max_eat_count_enabled = false;
	}
	return (status);
}

t_status	init_data(t_data *data, int argc, char **argv)
{
	t_status	status;

	status = SUCCESS;
	if (util_atoi(&data->num_of_philo, argv[1], NUM_OF_PHILO) == FAILURE)
		status = FAILURE;
	if (data->num_of_philo > 200 && status == SUCCESS)
	{
		status = FAILURE;
		printf("number_of_philosophers cannot be more than 200\n");
	}
	if (util_atoi(&data->time_to_die, argv[2], TIME_TO_DIE) == FAILURE)
		status = FAILURE;
	if (util_atoi(&data->time_to_eat, argv[3], TIME_TO_EAT) == FAILURE)
		status = FAILURE;
	if (util_atoi(&data->time_to_sleep, argv[4], TIME_TO_SLEEP) == FAILURE)
		status = FAILURE;
	status = get_max_eat_count(data, argc, argv);
	if (status == SUCCESS)
		status = init_mutexes(status, data);
	return (status);
}

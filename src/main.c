/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 16:19:59 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/30 11:24:26 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <string.h>

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

static t_status	init_data(t_data *data, int argc, char **argv)
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
	return (status);
}

static void	add_values(t_data *data, t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		philos[i].times_eaten = 0;
		philos[i].data = data;
		i++;
	}
}

static t_status	init_philos(t_data *data, t_philo **philos)
{
	*philos = my_calloc(data->num_of_philo, sizeof(t_philo));
	if (*philos == NULL)
		return (FAILURE);
	add_values(data, *philos);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	philos = NULL;
	if (argc == 5 || argc == 6)
	{
		if (init_data(&data, argc, argv) == FAILURE)
			return (EXIT_FAILURE);
		if (init_philos(&data, &philos) == FAILURE)
			return (EXIT_FAILURE);
		start_threads(&data, philos);
	}
	return (EXIT_SUCCESS);
}

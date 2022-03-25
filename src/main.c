/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 16:19:59 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/25 19:40:45 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

// can do this cleaner
static t_status	error_negative(t_arguments arg)
{
	if (arg == NUMBER_OF_PHILOSOPHERS)
		printf("number_of_philosophers");
	else if (arg == TIME_TO_DIE)
		printf("time_to_die");
	else if (arg == TIME_TO_EAT)
		printf("time_to_eat");
	else if (arg == TIME_TO_SLEEP)
		printf("time_to_sleep");
	else if (arg == MAX_EAT_COUNT)
		printf("number_of_times_each_philosopher_must_eat");
	printf(" cannot be negative\n");
	return (FAILURE);
}

static t_status	error_zero(t_arguments arg)
{
	if (arg == NUMBER_OF_PHILOSOPHERS)
		printf("number_of_philosophers");
	else if (arg == TIME_TO_DIE)
		printf("time_to_die");
	else if (arg == TIME_TO_EAT)
		printf("time_to_eat");
	else if (arg == TIME_TO_SLEEP)
		printf("time_to_sleep");
	else if (arg == MAX_EAT_COUNT)
		printf("number_of_times_each_philosopher_must_eat");
	printf(" cannot be zero\n");
	return (FAILURE);
}

static t_status	philo_atoi(size_t *num, char *str, t_arguments arg)
{
	int	i;

	*num = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		return (error_negative(arg));
	if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= 48 && str[i] <= 57)
	{
		*num = *num * 10 + str[i] - 48;
		i++;
	}
	if (*num < 0)
		return (error_negative(arg));
	if (*num == 0)
		return (error_zero(arg));
	return (SUCCESS);
}

static t_status	init_data(t_data *data, int argc, char **argv)
{
	printf("philo_atoi return: %d\n", philo_atoi(&data->number_of_philosophers, argv[1], NUMBER_OF_PHILOSOPHERS));
	printf("philo_atoi return: %d\n", philo_atoi(&data->time_to_die, argv[2], TIME_TO_DIE));
	printf("philo_atoi return: %d\n", philo_atoi(&data->time_to_eat, argv[3], TIME_TO_EAT));
	printf("philo_atoi return: %d\n", philo_atoi(&data->time_to_sleep, argv[4], TIME_TO_SLEEP));
	if (argc == 6)
		printf("philo_atoi return: %d\n", philo_atoi(&data->max_eat_count, argv[5], MAX_EAT_COUNT));
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (init_data(&data, argc, argv) == FAILURE)
			return (EXIT_FAILURE);
	}
	printf("%zu\n", data.number_of_philosophers);
	printf("%zu\n", data.time_to_die);
	printf("%zu\n", data.time_to_eat);
	printf("%zu\n", data.time_to_sleep);
	printf("%zu\n", data.max_eat_count);
	return (EXIT_SUCCESS);
}

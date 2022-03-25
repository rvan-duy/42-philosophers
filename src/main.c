/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 16:19:59 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/25 17:40:55 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static t_return_status	error_negative(int argument_num)
{
	if (argument_num == NUMBER_OF_PHILOSOPHERS)
		printf("number_of_philosophers");
	else if (argument_num == TIME_TO_DIE)
		printf("time_to_die");
	else if (argument_num == TIME_TO_EAT)
		printf("time_to_eat");
	else if (argument_num == TIME_TO_SLEEP)
		printf("time_to_sleep");
	else if (argument_num == MAX_EAT_COUNT)
		printf("number_of_times_each_philosopher_must_eat");
	printf(" cannot be negative\n");
	return (FAILURE);
}

static t_return_status	error_zero(int argument_num)
{
	if (argument_num == NUMBER_OF_PHILOSOPHERS)
		printf("number_of_philosophers");
	else if (argument_num == TIME_TO_DIE)
		printf("time_to_die");
	else if (argument_num == TIME_TO_EAT)
		printf("time_to_eat");
	else if (argument_num == TIME_TO_SLEEP)
		printf("time_to_sleep");
	else if (argument_num == MAX_EAT_COUNT)
		printf("number_of_times_each_philosopher_must_eat");
	printf(" cannot be zero\n");
	return (FAILURE);
}

static size_t	philo_atoi(char *str, int argument_num)
{
	int	number;
	int	i;

	number = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		return (error_negative(argument_num));
	if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= 48 && str[i] <= 57)
	{
		number = number * 10 + str[i] - 48;
		i++;
	}
	if (number < 0)
		return (error_negative(argument_num));
	if (number == 0)
		return (error_zero(argument_num));
	return (number);
}

static t_return_status	init_data(t_data *data, int argc, char **argv)
{
	data->number_of_philosophers = philo_atoi(argv[1], 1);
	data->time_to_die = philo_atoi(argv[2], 2);
	data->time_to_eat = philo_atoi(argv[3], 3);
	data->time_to_sleep = philo_atoi(argv[4], 4);
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
	return (EXIT_SUCCESS);
}

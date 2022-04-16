/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 16:19:59 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/16 17:51:12 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

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
		destroy_data(&data);
		destroy_philos(&philos);
	}
	else
		printf("Usage:\n%s <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_\
philosopher_must_eat]\n", argv[0]);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_threads.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/26 16:44:32 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/05/19 19:08:04 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status	create_threads(size_t num, pthread_t *threads, t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		if (pthread_create(&threads[i], NULL, &routine, &philos[i]) != SUCCESS)
			return (FAILURE);
		i++;
		usleep(SLEEP_INBETWEEN_PHILO_START);
	}
	return (SUCCESS);
}

static t_status	wait_for_threads(size_t num, pthread_t *threads)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		if (pthread_join(threads[i], NULL) != SUCCESS)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

t_status	start_threads(t_data *data, t_philo *philos)
{
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * data->num_of_philo);
	if (threads == NULL)
		return (FAILURE);
	data->start_time = get_time_in_ms();
	if (create_threads(data->num_of_philo, threads, philos) == FAILURE)
		return (FAILURE);
	if (wait_for_threads(data->num_of_philo, threads) == FAILURE)
		return (FAILURE);
	free(threads);
	return (SUCCESS);
}

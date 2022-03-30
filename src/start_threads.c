/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_threads.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/26 16:44:32 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/30 20:11:10 by rvan-duy      ########   odam.nl         */
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
		usleep(100);
		i++;
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

static void	check_for_deads(size_t num, t_philo *philos)
{
	size_t	i;

	while (true)
	{
		i = 0;
		while (i < num)
		{
			if (philos[i].time_since_last_meal > philos[i].data->time_to_die)
			{
				pthread_mutex_lock(&philos[i].data->philo_died_lock);
				protected_print("died", philos);
				philos[i].data->philo_died = true;
				pthread_mutex_unlock(&philos[i].data->philo_died_lock);
				return ;
				i++;
			}
		}
	}
}

t_status	start_threads(t_data *data, t_philo *philos)
{
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * data->num_of_philo);
	if (threads == NULL)
		return (FAILURE);
	if (create_threads(data->num_of_philo, threads, philos) == FAILURE)
		return (FAILURE);
	check_for_deads(data->num_of_philo, philos);
	if (wait_for_threads(data->num_of_philo, threads) == FAILURE)
		return (FAILURE);
	free(threads);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_threads.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/26 16:44:32 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/05/22 13:09:19 by rvan-duy      ########   odam.nl         */
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

static void	monitor_threads(t_philo *p)
{
	const t_timestamp	time_to_die = p->data->time_to_die;
	t_timestamp			current_time;
	size_t				i;

	while (true)
	{
		i = 0;
		while (i < p->data->num_of_philo)
		{
			current_time = get_timestamp(p[i].data->start_time);
			pthread_mutex_lock(p[i].last_meal_lock);
			if (current_time - p[i].last_meal > time_to_die)
			{
				pthread_mutex_unlock(p[i].last_meal_lock);
				print_dead(&p[i], current_time);
				return ;
			}
			pthread_mutex_unlock(p[i].last_meal_lock);
			i++;
		}
		usleep(MONITORING_DELAY);
	}
	return ;
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
	monitor_threads(philos);
	if (wait_for_threads(data->num_of_philo, threads) == FAILURE)
		return (FAILURE);
	free(threads);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_threads.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/26 16:44:32 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/12 15:05:09 by rvan-duy      ########   odam.nl         */
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

// static bool	everyone_is_full(size_t num, t_philo *philos)
// {
// 	size_t	i;
// 	size_t	sum;

// 	i = 0;
// 	sum = 0;
// 	while (i < num)
// 	{
// 		pthread_mutex_lock(&philos[i].data->extra_lock);
// 		sum += philos[i].times_eaten;
// 		pthread_mutex_unlock(&philos[i].data->extra_lock);
// 		i++;
// 	}
// 	return (sum == (philos[--i].data->max_eat_count * num));
// }

// static void	check_for_deads(t_data *data, t_philo *p)
// {
// 	size_t	i;

// 	while (true)
// 	{
// 		i = 0;
// 		while (i < data->num_of_philo)
// 		{
// 			pthread_mutex_lock(&data->extra_lock);
// 			if (p[i].time_since_last_meal > data->time_to_die)
// 			{
// 				p[i].data->end_reached = true;
// 				p[i].is_alive = false;
// 				pthread_mutex_lock(&p->data->print_lock);
// 				printf("%zu %zu died\n", get_timestamp(p->data->start_time), p->seat);
// 				pthread_mutex_unlock(&p->data->print_lock);
// 				pthread_mutex_unlock(&data->extra_lock);
// 				return ;
// 			}
// 			pthread_mutex_unlock(&p[i].data->extra_lock);
// 			if (everyone_is_full(data->num_of_philo, p) == true)
// 				return ;
// 			i++;
// 		}
// 	}
// }

t_status	start_threads(t_data *data, t_philo *philos)
{
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * data->num_of_philo);
	if (threads == NULL)
		return (FAILURE);
	data->start_time = get_time_in_ms();
	if (create_threads(data->num_of_philo, threads, philos) == FAILURE)
		return (FAILURE);
	// check_for_deads(data, philos);
	if (wait_for_threads(data->num_of_philo, threads) == FAILURE)
		return (FAILURE);
	free(threads);
	return (SUCCESS);
}

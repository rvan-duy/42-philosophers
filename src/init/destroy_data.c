/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   destroy_data.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 18:12:48 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/05/26 14:36:41 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_data(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->last_meal_lock[i]);
		pthread_mutex_destroy(&data->times_eaten_lock[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->philo_died_lock);
	free(data->forks);
	free(data->last_meal_lock);
	free(data->times_eaten_lock);
}

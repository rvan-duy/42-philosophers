/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_philos.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 14:14:00 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/03 17:19:54 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	add_values(t_data *data, t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		philos[i].seat = i;
		philos[i].is_alive = true;
		philos[i].times_eaten = 0;
		philos[i].time_since_last_meal = 0;
		philos[i].timestamp_last_meal = 0;
		philos[i].data = data;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->num_of_philo];
		i++;
	}
	if (philos[i].left_fork == philos[i].right_fork)
		philos[i].right_fork = NULL;
}

t_status	init_philos(t_data *data, t_philo **philos)
{
	*philos = my_calloc(data->num_of_philo, sizeof(t_philo));
	if (*philos == NULL)
		return (FAILURE);
	add_values(data, *philos);
	return (SUCCESS);
}

void	destroy_philos(t_philo **philos)
{
	free(*philos);
}

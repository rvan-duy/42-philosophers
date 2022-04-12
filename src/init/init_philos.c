/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_philos.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 14:14:00 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/12 15:04:54 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	add_values(t_data *data, t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		philos[i].seat = i + 1;
		philos[i].is_alive = true;
		philos[i].times_eaten = 0;
		philos[i].last_meal = 0;
		philos[i].data = data;
		philos[i].state = THINK;
		philos[i].left_fork = &data->forks[i];
		if (philos[i].data->num_of_philo > 1)
			philos[i].right_fork = &data->forks[(i + 1) % data->num_of_philo];
		i++;
	}
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

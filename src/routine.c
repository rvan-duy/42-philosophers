/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 11:35:18 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/30 19:47:49 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool has_eaten_enough(t_philo *philo_data)
{
	if (philo_data->times_eaten == philo_data->data->max_eat_count)
		return (true);
	return (false);
}

void	*routine(void *arg)
{
	go_eat(arg);
	while (true)
	{
		go_sleep(arg);
		go_think(arg);
		if (has_eaten_enough(arg) == true || check_if_dead(arg) == true)
			break ;
	}
	return (NULL);
}

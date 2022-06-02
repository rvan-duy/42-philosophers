/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 14:13:48 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/06/02 15:37:46 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	has_eaten_enough(t_philo *p)
{
	if (p->data->max_eat_count_enabled == false)
		return (false);
	pthread_mutex_lock(p->times_eaten_lock);
	if (p->times_eaten == p->data->max_eat_count)
	{
		pthread_mutex_unlock(p->times_eaten_lock);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(p->times_eaten_lock);
		return (false);
	}
}

static bool	is_supposed_to_die(t_philo *p)
{
	const t_timestamp	time_to_die = p->data->time_to_die;
	t_timestamp			current_time;

	current_time = get_timestamp(p->data->start_time);
	pthread_mutex_lock(p->last_meal_lock);
	if (current_time - p->last_meal > time_to_die)
	{
		pthread_mutex_unlock(p->last_meal_lock);
		print_dead(p, current_time);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(p->last_meal_lock);
		return (false);
	}
}

static bool	all_philos_are_finished(t_philo *p, size_t philos_finished)
{
	pthread_mutex_lock(&p->data->philo_died_lock);
	if (philos_finished == p->data->num_of_philo)
	{
		p->data->a_philo_died = true;
		pthread_mutex_unlock(&p->data->philo_died_lock);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&p->data->philo_died_lock);
		return (false);
	}
}

void	monitor_threads(t_philo *p)
{
	size_t	i;
	size_t	philos_finished;

	while (true)
	{
		i = 0;
		philos_finished = 0;
		while (i < p->data->num_of_philo)
		{
			if (has_eaten_enough(&p[i]) == true)
				philos_finished++;
			if (is_supposed_to_die(&p[i]) == true)
				return ;
			i++;
		}
		if (all_philos_are_finished(p, philos_finished) == true)
			return ;
		usleep(MONITORING_DELAY);
	}
	return ;
}

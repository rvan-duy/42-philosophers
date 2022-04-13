/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 11:35:18 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/13 14:48:30 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

// each thread needs separate thread to check for dead / enough_eaten
// then you dont have to check every single time?

// [1-200] 800 200 200

static bool	philo_should_die(t_timestamp *current_timestamp, t_philo *p)
{
	pthread_mutex_lock(&p->data->extra_lock);
	*current_timestamp = get_timestamp(p->data->start_time);
	if (*current_timestamp - p->last_meal >= p->data->time_to_die
		&& p->state != EAT)
		return (true);
	return (false);
}

static void	*maintainer_thread(void *arg)
{
	t_philo		*p;
	t_timestamp	current_timestamp;

	p = arg;
	while (true)
	{
		if (check_end(p) == true)
			return (NULL);
		pthread_mutex_lock(&p->data->extra_lock);
		if (p->ate_enough == true)
		{
			pthread_mutex_unlock(&p->data->extra_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&p->data->extra_lock);
		if (philo_should_die(&current_timestamp, arg) == true)
		{
			if (p->data->end_reached == false)
			{
				pthread_mutex_lock(&p->data->print_lock);
				printf("%zu %zu died\n", current_timestamp, p->seat);
				pthread_mutex_unlock(&p->data->print_lock);
			}
			p->data->end_reached = true;
			pthread_mutex_unlock(&p->data->extra_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&p->data->extra_lock);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	pthread_t	maintainer;

	pthread_create(&maintainer, NULL, &maintainer_thread, arg);
	go_eat(arg);
	while (true)
	{
		if (check_end(arg) == true)
			break ;
		go_sleep(arg);
		if (check_end(arg) == true)
			break ;
		go_think(arg);
		if (check_if_ate_enough(arg) == true)
			break ;
		if (check_end(arg) == true)
			break ;
	}
	pthread_join(maintainer, NULL);
	return (NULL);
}

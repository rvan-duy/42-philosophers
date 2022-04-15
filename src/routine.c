/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 11:35:18 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/15 18:46:04 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

// each thread needs separate thread to check for dead / enough_eaten
// then you dont have to check every single time?

// [1-200] 800 200 200

static bool	philo_should_die(t_timestamp *current_timestamp, t_philo *p)
{
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
		pthread_mutex_lock(&p->data->extra_lock);
		if (p->data->end_reached == true
			|| p->times_eaten >= p->data->max_eat_count)
			break ;
		if (philo_should_die(&current_timestamp, arg) == true)
		{
			if (p->data->end_reached == false)
			{
				pthread_mutex_lock(&p->data->print_lock);
				p->data->end_reached = true;
				printf("%zu %zu died\n", current_timestamp, p->seat);
				pthread_mutex_unlock(&p->data->print_lock);
			}
		}
		pthread_mutex_unlock(&p->data->extra_lock);
	}
	pthread_mutex_unlock(&p->data->extra_lock);
	return (NULL);
}

void	*routine(void *arg)
{
	pthread_t	maintainer;
	t_philo		*p;

	p = arg;
	pthread_create(&maintainer, NULL, &maintainer_thread, arg);
	go_eat(arg);
	while (true)
	{
		go_sleep(arg);
		go_think(arg);
		if (p->times_eaten >= p->data->max_eat_count)
			break ;
		if (check_end(arg) == true)
			break ;
	}
	pthread_join(maintainer, NULL);
	return (NULL);
}

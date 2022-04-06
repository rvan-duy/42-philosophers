/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 11:35:18 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/06 21:11:03 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// each thread needs separate thread to check for dead / enough_eaten
// then you dont have to check every single time?

// infinite loop:
// updates times
// if times exceed something then we die

static void	*maintainer_thread(void *arg)
{
	t_philo		*p;
	t_timestamp	current_timestamp;

	p = arg;
	while (true)
	{
		// probably need locks to avoid data from getting fucky
		current_timestamp = get_timestamp(p->data->start_time);
		if (current_timestamp - p->last_meal > p->data->time_to_die &&
			p->state != EAT)
		{
			printf("current_timestamp: %zu last_meal: %zu p->data->time_to_die: %zu\n", current_timestamp, p->last_meal, p->data->time_to_die);
			printf("%zu died\n", p->seat);
			p->is_alive = false;
			return (NULL);
		}
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
		if (check_if_alive(arg) == true)
			return (NULL);
		go_sleep(arg);
		if (check_if_alive(arg) == true)
			return (NULL);
		go_think(arg);
		if (check_if_ate_enough(arg) == true)
			return (NULL);
		if (check_if_alive(arg) == true)
			return (NULL);
	}
	return (NULL);
}

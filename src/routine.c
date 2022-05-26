/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 11:35:18 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/05/25 16:09:19 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*p;

	p = arg;
	if (p->seat % 2 == 0)
		usleep(ODD_PHILO_WAIT_TIME_BEFORE_START);
	while (true)
	{
		go_eat(p);
		pthread_mutex_lock(p->times_eaten_lock);
		pthread_mutex_unlock(p->times_eaten_lock);
		go_sleep(p);
		go_think(p);
		pthread_mutex_lock(&p->data->philo_died_lock);
		if (p->data->a_philo_died == true)
		{
			pthread_mutex_unlock(&p->data->philo_died_lock);
			break ;
		}
		pthread_mutex_unlock(&p->data->philo_died_lock);
	}
	return (NULL);
}

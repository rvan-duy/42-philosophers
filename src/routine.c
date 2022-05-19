/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 11:35:18 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/05/19 19:07:46 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo *p;

	p = arg;
	if (p->seat % 2 == 0)
		usleep(ODD_PHILO_WAIT_TIME_BEFORE_START);
	while (true)
	{
		go_eat(p);
		go_sleep(p);
		go_think(p);
		pthread_mutex_lock(&p->data->extra_lock);
		if (p->data->a_philo_died == true)
		{
			pthread_mutex_unlock(&p->data->extra_lock);
			break ;
		}
		pthread_mutex_unlock(&p->data->extra_lock);
	}
	return (NULL);
}

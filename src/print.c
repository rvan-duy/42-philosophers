/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/19 14:56:22 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/05/26 13:23:16 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_dead(t_philo *p, const t_timestamp current_time)
{
	pthread_mutex_lock(&p->data->philo_died_lock);
	p->data->a_philo_died = true;
	pthread_mutex_unlock(&p->data->philo_died_lock);
	pthread_mutex_lock(&p->data->print_lock);
	printf("%zu %zu died\n", current_time, p->seat);
	pthread_mutex_unlock(&p->data->print_lock);
}

bool	is_dead(t_philo *p)
{
	pthread_mutex_lock(&p->data->philo_died_lock);
	if (p->data->a_philo_died == true)
	{
		pthread_mutex_unlock(&p->data->philo_died_lock);
		return (true);
	}
	pthread_mutex_unlock(&p->data->philo_died_lock);
	return (false);
}

bool	print_message(const char *message, t_philo *p)
{
	if (is_dead(p) == false)
	{
		pthread_mutex_lock(&p->data->print_lock);
		printf("%zu %zu %s\n", get_timestamp(p->data->start_time), \
					p->seat, message);
		pthread_mutex_unlock(&p->data->print_lock);
		return (true);
	}
	return (false);
}

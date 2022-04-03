/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/27 14:19:15 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/03 17:41:20 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void	*my_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (ptr);
	memset(ptr, 0, nmemb * size);
	return (ptr);
}

void	protected_print(char *msg, t_philo *p)
{
	if (check_end_condition(p) == false)
	{
		pthread_mutex_lock(&p->data->print_lock);
		printf("%zu %zu %s\n", get_timestamp(p->data->start_time), p->seat, msg);
		pthread_mutex_unlock(&p->data->print_lock);
	}
}

bool	check_end_condition(t_philo *p)
{
	pthread_mutex_lock(&p->data->extra_lock);
	if (p->data->a_philo_died == true)
	{
		pthread_mutex_unlock(&p->data->extra_lock);
		return (true);
	}
	pthread_mutex_unlock(&p->data->extra_lock);
	update_time_since_last_meal(p);
	if (p->time_since_last_meal >= p->data->time_to_die)
	{
		pthread_mutex_lock(&p->data->extra_lock);
		p->is_alive = false;
		pthread_mutex_unlock(&p->data->extra_lock);
		pthread_mutex_lock(&p->data->print_lock);
		printf("%zu %zu died\n", get_timestamp(p->data->start_time), p->seat);
		pthread_mutex_unlock(&p->data->print_lock);
		return (true);
	}
	return (false);
}

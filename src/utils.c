/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/27 14:19:15 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/12 16:55:20 by rvan-duy      ########   odam.nl         */
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
	if (check_end(p) == false)
	{
		pthread_mutex_lock(&p->data->extra_lock);
		if (p->data->end_reached == true)
		{
			pthread_mutex_unlock(&p->data->extra_lock);
			return ;
		}
		pthread_mutex_unlock(&p->data->extra_lock);
		pthread_mutex_lock(&p->data->print_lock);
		printf("%zu %zu %s\n", get_timestamp(p->data->start_time), p->seat, msg);
		pthread_mutex_unlock(&p->data->print_lock);
	}
}

bool	check_end(t_philo *p)
{
	pthread_mutex_lock(&p->data->extra_lock);
	if (p->data->end_reached == true)
	{
		pthread_mutex_unlock(&p->data->extra_lock);
		return (true);
	}
	pthread_mutex_unlock(&p->data->extra_lock);
	return (false);
}

bool	check_if_ate_enough(t_philo *p)
{
	pthread_mutex_lock(&p->data->extra_lock);
	if (p->times_eaten >= p->data->max_eat_count)
	{
		p->is_alive = false;
		pthread_mutex_unlock(&p->data->extra_lock);
		return (true);
	}
	pthread_mutex_unlock(&p->data->extra_lock);
	return (false);
}

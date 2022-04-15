/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/27 14:19:15 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/15 18:42:41 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <stdio.h>

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
	pthread_mutex_lock(&p->data->print_lock);
	if (p->data->end_reached == false)
	{
		printf("%zu %zu %s\n", get_timestamp(p->data->start_time), p->seat, msg);
	}
	pthread_mutex_unlock(&p->data->print_lock);
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

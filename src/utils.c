/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/27 14:19:15 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/30 16:33:54 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <sys/time.h>

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

int	my_usleep(useconds_t microseconds)
{
	struct timeval	current_time;
	struct timeval	target_time;

	gettimeofday(&current_time, NULL);
	target_time.tv_usec = current_time.tv_usec + microseconds;
	while (current_time.tv_usec < target_time.tv_usec)
	{
		if (usleep(1) != SUCCESS)
			return (FAILURE);
		current_time.tv_usec++;
	}
	return (SUCCESS);
}

useconds_t	get_timestamp(t_data *data)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (((current_time.tv_usec - data->start_time.tv_usec) / 1000) \
				+ ((current_time.tv_sec - data->start_time.tv_sec) * 1000));
}

void	protected_print(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%u %zu %s\n", get_timestamp(philo->data), philo->seat, msg);
	pthread_mutex_unlock(&philo->data->print_lock);
}

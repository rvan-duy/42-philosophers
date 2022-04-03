/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/27 14:19:15 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/03 15:22:32 by rvan-duy      ########   odam.nl         */
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

void	protected_print(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_lock);
	if (check_end_condition(philo) == false)
		printf("%zu %zu %s\n", get_timestamp(philo->data->start_time), philo->seat, msg);
	pthread_mutex_unlock(&philo->data->print_lock);
}

bool	check_end_condition(t_philo *philo_data)
{
	bool	ret;

	pthread_mutex_lock(&philo_data->data->extra_lock);
	if (philo_data->times_eaten >= philo_data->data->max_eat_count
		|| philo_data->data->philo_died == true)
		ret = true;
	else
		ret = false;
	pthread_mutex_unlock(&philo_data->data->extra_lock);
	return (ret);
}

void	update_time_since_last_meal(t_philo *philo)
{
	const size_t	current_timestamp = get_timestamp(philo->data->start_time);

	pthread_mutex_lock(&philo->data->extra_lock);
	philo->time_since_last_meal = philo->data->start_time - current_timestamp;
	pthread_mutex_unlock(&philo->data->extra_lock);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/27 14:19:15 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/31 19:09:35 by rvan-duy      ########   odam.nl         */
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

long long	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000LL + time.tv_usec / 1000);
}

long long	get_timestamp(long long start_timestamp)
{
	return (get_time_in_ms() - start_timestamp);
}

static unsigned long	get_time_us(void)
{
	static struct timeval	tv;
	unsigned long			out;

	gettimeofday(&tv, NULL);
	out = tv.tv_sec;
	out *= 1e6;
	out += tv.tv_usec;
	return (out);
}

void    stupid_sleep(unsigned long time2sleep)
{
	unsigned long	start;

	start = get_time_us();
	time2sleep *= 1000;
	while (get_time_us() - start < time2sleep)
		usleep(100);
}

void	protected_print(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_lock);
	if (check_end_condition(philo) == false)
		printf("%lld %zu %s\n", get_timestamp(philo->data->start_time), philo->seat, msg);
	pthread_mutex_unlock(&philo->data->print_lock);
}

bool	check_end_condition(t_philo *philo_data)
{
	if (philo_data->times_eaten >= philo_data->data->max_eat_count
		|| philo_data->data->philo_died == true)
		return (true);
	return (false);
}

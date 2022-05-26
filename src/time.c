/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/03 12:46:51 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/05/26 13:33:18 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

t_timestamp	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000LL + time.tv_usec / 1000);
}

t_timestamp	get_timestamp(const t_timestamp start_time)
{
	return (get_time_in_ms() - start_time);
}

static size_t	get_time_us(void)
{
	static struct timeval	tv;
	size_t					out;

	gettimeofday(&tv, NULL);
	out = tv.tv_sec;
	out *= 1e6;
	out += tv.tv_usec;
	return (out);
}

void	stupid_sleep(size_t time2sleep)
{
	size_t	start;

	start = get_time_us();
	time2sleep *= 1000;
	while (get_time_us() - start < time2sleep)
		usleep(250);
}

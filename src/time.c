/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/03 12:46:51 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/03 12:48:48 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

static long long	get_time_in_ms(void)
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

void	stupid_sleep(unsigned long time2sleep)
{
	unsigned long	start;

	start = get_time_us();
	time2sleep *= 1000;
	while (get_time_us() - start < time2sleep)
		usleep(100);
}

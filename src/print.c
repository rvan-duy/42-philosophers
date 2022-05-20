/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/19 14:56:22 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/05/20 11:37:18 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_dead(t_philo *p, const t_timestamp current_time)
{
	pthread_mutex_lock(&p->data->extra_lock);
	p->data->a_philo_died = true;
	pthread_mutex_unlock(&p->data->extra_lock);
	pthread_mutex_lock(&p->data->print_lock);
	util_putnbr_fd(current_time, STDOUT_FILENO);
	util_putchar_fd(' ', STDOUT_FILENO);
	util_putnbr_fd(p->seat, STDOUT_FILENO);
	util_putstr_fd(" died", STDOUT_FILENO);
	util_putchar_fd('\n', STDOUT_FILENO);
	pthread_mutex_unlock(&p->data->print_lock);
}

bool	is_dead(t_philo *p)
{
	const t_timestamp	current_time = get_timestamp(p->data->start_time);

	pthread_mutex_lock(&p->data->extra_lock);
	if (p->data->a_philo_died == true)
	{
		pthread_mutex_unlock(&p->data->extra_lock);
		return (true);
	}
	pthread_mutex_unlock(&p->data->extra_lock);
	pthread_mutex_lock(&p->data->print_lock);
	util_putnbr_fd(p->seat, STDOUT_FILENO);
	util_putchar_fd(' ', STDOUT_FILENO);
	util_putnbr_fd(current_time, STDOUT_FILENO);
	util_putchar_fd(' ', STDOUT_FILENO);
	util_putnbr_fd(p->last_meal, STDOUT_FILENO);
	util_putchar_fd('\n', STDOUT_FILENO);
	pthread_mutex_unlock(&p->data->print_lock);
	if (current_time - p->last_meal >= p->data->time_to_die)
	{
		print_dead(p, current_time);
		return (true);
	}
	return (false);
}

bool	print_message(const char *message, t_philo *p)
{
	const t_timestamp	current_time = get_timestamp(p->data->start_time);

	if (is_dead(p) == false)
	{
		pthread_mutex_lock(&p->data->print_lock);
		util_putnbr_fd(current_time, STDOUT_FILENO);
		util_putchar_fd(' ', STDOUT_FILENO);
		util_putnbr_fd(p->seat, STDOUT_FILENO);
		util_putchar_fd(' ', STDOUT_FILENO);
		util_putstr_fd(message, STDOUT_FILENO);
		util_putchar_fd('\n', STDOUT_FILENO);
		pthread_mutex_unlock(&p->data->print_lock);
		return (true);
	}
	return (false);
}

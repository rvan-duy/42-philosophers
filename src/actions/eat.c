/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 14:50:19 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/05/19 20:13:59 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool grab_fork(pthread_mutex_t *fork, t_philo *p)
{
	if (fork == NULL)
	{
		stupid_sleep(p->data->time_to_die);
		return (false);
	}
	pthread_mutex_lock(fork);
	return (print_message("has taken a fork", p));
}

static void grab_forks(t_philo *p)
{
	if (grab_fork(p->left_fork, p) == false)
	{
		pthread_mutex_unlock(p->left_fork);
		return ;
	}
	if (grab_fork(p->right_fork, p) == false)
	{
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
		return ;
	}
	return ;
}

static void drop_forks(t_philo *p)
{
	if (p->left_fork != NULL)
		pthread_mutex_unlock(p->left_fork);
	if (p->right_fork != NULL)
		pthread_mutex_unlock(p->right_fork);
}

void	go_eat(t_philo *p)
{
	// t_timestamp current_time;
	// t_timestamp time_philo_will_die;

	grab_forks(p);
	
	if (print_message("is eating", p) == false)
		return ;
		
	// current_time = get_timestamp(p->data->start_time);
	
	// pthread_mutex_lock(&p->data->print_lock);
	// util_putnbr_fd(p->seat, 1);
	// util_putstr_fd(" current_time:", 1);
	// util_putnbr_fd(current_time, 1);
	// util_putstr_fd(" last_meal:", 1);
	// util_putnbr_fd(p->last_meal, 1);
	// util_putchar_fd('\n', 1);
	// pthread_mutex_unlock(&p->data->print_lock);
	
	// time_philo_will_die = p->data->time_to_die - (current_time - p->last_meal);
	
	// pthread_mutex_lock(&p->data->print_lock);
	// util_putnbr_fd(p->seat, 1);
	// util_putstr_fd(" time_to_eat:", 1);
	// util_putnbr_fd(p->data->time_to_eat, 1);
	// util_putstr_fd(" time_philo_will_die:", 1);
	// util_putnbr_fd(time_philo_will_die, 1);
	// util_putchar_fd('\n', 1);
	// pthread_mutex_unlock(&p->data->print_lock);

	// if (p->data->time_to_eat > time_philo_will_die)
	// {
	// 	stupid_sleep(time_philo_will_die);
	// 	print_message("is dead", p);
	// 	drop_forks(p);
	// 	return ;
	// }
	p->last_meal = get_timestamp(p->data->start_time);
	stupid_sleep(p->data->time_to_eat);
	drop_forks(p);
	p->times_eaten++;
}

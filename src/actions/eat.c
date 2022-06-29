/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 14:50:19 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/06/29 12:54:05 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	grab_fork(pthread_mutex_t *fork, t_philo *p)
{
	if (fork == NULL)
	{
		stupid_sleep(p->data->time_to_die);
		return (false);
	}
	pthread_mutex_lock(fork);
	return (print_message("has taken a fork", p));
}

static void	grab_forks(t_philo *p)
{
	if (grab_fork(p->left_fork, p) == false)
	{
		return ;
	}
	if (grab_fork(p->right_fork, p) == false)
	{
		pthread_mutex_unlock(p->left_fork);
		return ;
	}
	return ;
}

static void	drop_forks(t_philo *p)
{
	if (p->left_fork != NULL)
		pthread_mutex_unlock(p->left_fork);
	if (p->right_fork != NULL)
		pthread_mutex_unlock(p->right_fork);
}

void	go_eat(t_philo *p)
{
	grab_forks(p);
	if (p->left_fork == NULL || p->right_fork == NULL)
		return ;
	if (print_message("is eating", p) == false)
		return ;
	pthread_mutex_lock(p->last_meal_lock);
	p->last_meal = get_timestamp(p->data->start_time);
	pthread_mutex_unlock(p->last_meal_lock);
	stupid_sleep(p->data->time_to_eat);
	drop_forks(p);
	pthread_mutex_lock(p->times_eaten_lock);
	p->times_eaten++;
	pthread_mutex_unlock(p->times_eaten_lock);
}

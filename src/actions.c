/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 14:55:50 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/03 18:02:48 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	grab_fork(pthread_mutex_t *fork, t_philo *p)
{
	if (fork != NULL)
	{
		pthread_mutex_lock(fork);
		protected_print("has taken a fork", p);
	}
	else
	{
		stupid_sleep(p->data->time_to_die);
	}
}

static void	hold_forks(t_philo *p)
{
	if (p->seat % 2 == 0)
	{
		if (check_end_condition(p) == false)
		{
			grab_fork(p->left_fork, p);
			if (check_end_condition(p) == false)
				grab_fork(p->right_fork, p);
			else
				pthread_mutex_unlock(p->left_fork);
		}
	}
	else
	{
		if (check_end_condition(p) == false)
		{
			grab_fork(p->right_fork, p);
			if (check_end_condition(p) == false)
				grab_fork(p->left_fork, p);
			else
				pthread_mutex_unlock(p->right_fork);
		}
	}
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
	hold_forks(p);
	if (check_end_condition(p) == true)
	{
		drop_forks(p);
		return ;
	}
	protected_print("is eating", p);
	stupid_sleep(p->data->time_to_eat);
	pthread_mutex_lock(&p->data->extra_lock);
	p->time_since_last_meal = 0;
	p->timestamp_last_meal = get_timestamp(p->data->start_time);
	p->times_eaten++;
	pthread_mutex_unlock(&p->data->extra_lock);
	drop_forks(p);
}

void	go_sleep(t_philo *p)
{
	protected_print("is sleeping", p);
	pthread_mutex_lock(&p->data->extra_lock);
	p->time_since_last_meal += p->data->time_to_sleep;
	pthread_mutex_unlock(&p->data->extra_lock);
	stupid_sleep(p->data->time_to_sleep);
}

void	go_think(t_philo *p)
{
	protected_print("is thinking", p);
	go_eat(p);
}

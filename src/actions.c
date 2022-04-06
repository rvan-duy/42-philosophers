/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 14:55:50 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/06 20:43:44 by rvan-duy      ########   odam.nl         */
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
		if (check_if_alive(p) == false)
		{
			grab_fork(p->left_fork, p);
			if (check_if_alive(p) == false)
				grab_fork(p->right_fork, p);
			else
				pthread_mutex_unlock(p->left_fork);
		}
	}
	else
	{
		if (check_if_alive(p) == false)
		{
			grab_fork(p->right_fork, p);
			if (check_if_alive(p) == false)
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
	if (check_if_alive(p) == true)
	{
		drop_forks(p);
		return ;
	}

	protected_print("is eating", p);
	p->state = EAT;
	stupid_sleep(p->data->time_to_eat);
	p->last_meal = get_timestamp(p->data->start_time);

	// stuff
	pthread_mutex_lock(&p->data->extra_lock);
	p->last_meal = get_timestamp(p->data->start_time);
	p->times_eaten++;
	pthread_mutex_unlock(&p->data->extra_lock);
	drop_forks(p);
}

void	go_sleep(t_philo *p)
{
	protected_print("is sleeping", p);
	p->state = SLEEP;
	stupid_sleep(p->data->time_to_sleep);
}

void	go_think(t_philo *p)
{
	protected_print("is thinking", p);
	p->state = THINK;
	go_eat(p);
}

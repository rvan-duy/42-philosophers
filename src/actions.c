/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 14:55:50 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/13 14:28:45 by rvan-duy      ########   odam.nl         */
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
	if (check_end(p) == false)
	{
		grab_fork(p->left_fork, p);
		if (check_end(p) == false)
			grab_fork(p->right_fork, p);
		else
		{
			pthread_mutex_unlock(p->left_fork);
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
	if (check_end(p) == true)
	{
		drop_forks(p);
		return ;
	}
	protected_print("is eating", p);
	pthread_mutex_lock(&p->data->extra_lock);
	p->state = EAT;
	pthread_mutex_unlock(&p->data->extra_lock);
	stupid_sleep(p->data->time_to_eat);
	drop_forks(p);
	pthread_mutex_lock(&p->data->extra_lock);
	p->last_meal = get_timestamp(p->data->start_time);
	p->times_eaten++;
	pthread_mutex_unlock(&p->data->extra_lock);
}

void	go_sleep(t_philo *p)
{
	protected_print("is sleeping", p);
	pthread_mutex_lock(&p->data->extra_lock);
	p->state = SLEEP;
	pthread_mutex_unlock(&p->data->extra_lock);
	stupid_sleep(p->data->time_to_sleep);
}

void	go_think(t_philo *p)
{
	protected_print("is thinking", p);
	pthread_mutex_lock(&p->data->extra_lock);
	p->state = THINK;
	pthread_mutex_unlock(&p->data->extra_lock);
	go_eat(p);
}

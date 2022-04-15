/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 14:50:19 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/15 14:50:47 by rvan-duy      ########   odam.nl         */
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
	if (p->data->end_reached == false)
	{
		grab_fork(p->left_fork, p);
		if (p->data->end_reached == false)
			grab_fork(p->right_fork, p);
		else
		{
			pthread_mutex_unlock(p->left_fork);
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
	if (p->data->end_reached == true)
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
	p->state = NOT_EAT;
	pthread_mutex_unlock(&p->data->extra_lock);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 14:55:50 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/03 15:27:07 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	grab_fork(pthread_mutex_t *fork, t_philo *philo_data)
{
	if (fork != NULL)
	{
		pthread_mutex_lock(fork);
		protected_print("has taken a fork", philo_data);
	}
}

static void	hold_forks(t_philo *philo_data)
{
	if (philo_data->seat % 2 == 0)
	{
		if (check_end_condition(philo_data) == false)
		{
			grab_fork(philo_data->left_fork, philo_data);
			if (check_end_condition(philo_data) == false)
				grab_fork(philo_data->right_fork, philo_data);
			else
				pthread_mutex_unlock(philo_data->left_fork);
		}
	}
	else
	{
		if (check_end_condition(philo_data) == false)
		{
			grab_fork(philo_data->right_fork, philo_data);
			if (check_end_condition(philo_data) == false)
				grab_fork(philo_data->left_fork, philo_data);
			else
				pthread_mutex_unlock(philo_data->right_fork);
		}
	}
}

static void	drop_forks(t_philo *philo_data)
{
	pthread_mutex_unlock(philo_data->left_fork);
	pthread_mutex_unlock(philo_data->right_fork);
}

void	go_eat(t_philo *philo_data)
{
	hold_forks(philo_data);
	if (check_end_condition(philo_data) == true)
	{
		drop_forks(philo_data);
		return ;
	}
	protected_print("is eating", philo_data);
	stupid_sleep(philo_data->data->time_to_eat);
	pthread_mutex_lock(&philo_data->data->extra_lock);
	philo_data->time_since_last_meal = 0;
	philo_data->times_eaten++;
	pthread_mutex_unlock(&philo_data->data->extra_lock);
	drop_forks(philo_data);
}

void	go_sleep(t_philo *philo_data)
{
	protected_print("is sleeping", philo_data);
	pthread_mutex_lock(&philo_data->data->extra_lock);
	philo_data->time_since_last_meal += philo_data->data->time_to_sleep;
	pthread_mutex_unlock(&philo_data->data->extra_lock);
	stupid_sleep(philo_data->data->time_to_sleep);
}

void	go_think(t_philo *philo_data)
{
	protected_print("is thinking", philo_data);
	go_eat(philo_data);
}

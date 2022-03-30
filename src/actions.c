/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 14:55:50 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/30 18:35:22 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	hold_forks(t_philo *philo_data)
{
	if (philo_data->seat % 2 == 0)
	{
		pthread_mutex_lock(philo_data->left_fork);
		protected_print("has taken a fork", philo_data);
		pthread_mutex_lock(philo_data->right_fork);
		protected_print("has taken a fork", philo_data);
	}
	else
	{
		pthread_mutex_lock(philo_data->right_fork);
		protected_print("has taken a fork", philo_data);
		pthread_mutex_lock(philo_data->left_fork);
		protected_print("has taken a fork", philo_data);
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
	protected_print("is eating", philo_data);
	my_usleep(philo_data->data->time_to_eat * 1000);
	philo_data->times_eaten++;
	drop_forks(philo_data);
}

void	go_sleep(t_philo *philo_data)
{
	protected_print("is sleeping", philo_data);
	my_usleep(philo_data->data->time_to_sleep * 1000);
}

void	go_think(t_philo *philo_data)
{
	protected_print("is thinking", philo_data);
	go_eat(philo_data);
}

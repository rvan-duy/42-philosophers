/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 14:51:44 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/05/19 20:19:38 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_sleep(t_philo *p)
{
	const t_timestamp current_time = get_timestamp(p->data->start_time);
	const t_timestamp time_till_philo_dies = p->data->time_to_die - (current_time - p->last_meal);

	if (p->data->time_to_sleep > time_till_philo_dies)
	{
		print_message("is sleeping", p);
		stupid_sleep(time_till_philo_dies);
		print_message("died", p);
		return ;
	}
	print_message("is sleeping", p);
	stupid_sleep(p->data->time_to_sleep);
}

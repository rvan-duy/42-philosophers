/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 14:51:44 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/05/20 13:59:02 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_sleep(t_philo *p)
{
	print_message("is sleeping", p);
	stupid_sleep(p->data->time_to_sleep);
}

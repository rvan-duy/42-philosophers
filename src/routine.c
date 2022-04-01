/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 11:35:18 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/31 19:08:05 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	go_eat(arg);
	while (true)
	{
		if (check_end_condition(arg) == true)
			return (NULL);
		go_sleep(arg);
		if (check_end_condition(arg) == true)
			return (NULL);
		go_think(arg);
		if (check_end_condition(arg) == true)
			return (NULL);
	}
	return (NULL);
}

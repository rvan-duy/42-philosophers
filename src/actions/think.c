/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   think.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 14:52:00 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/15 14:52:12 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_think(t_philo *p)
{
	protected_print("is thinking", p);
	go_eat(p);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 14:55:50 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/30 15:44:23 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// grab 2 forks
// eat for some time
void	eat(t_philo *philo_data)
{
	printf("%u\n", get_timestamp(philo_data->data));
	printf("left_fork: %p right_fork: %p\n", philo_data->left_fork, philo_data->right_fork);
	printf("Hoi %ld\n", philo_data->seat);
}

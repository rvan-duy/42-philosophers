/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_philos.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/26 16:44:32 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/27 15:24:51 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

# include <stdio.h>

// POSSIBLE SOLUTION:
// void f1(int **pointer)
// {

//     int number = 10;

//     *pointer = &number;

// }

// int main()
// {
//     int * pointer;

//     f1(&pointer);

//     printf("%d\n", *pointer);

//     return 0;
// }

static void	add_values(t_data *data, t_philo **philos)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		(*philos)[i].times_eaten = 0;
		(*philos)[i].data = data;
		i++;
	}
}

void	start_philos(t_data *data, t_philo **philos)
{
	add_values(data, philos);
	return ;
}

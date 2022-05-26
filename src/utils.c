/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/27 14:19:15 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/05/26 13:47:39 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static char	*get_argument(t_arguments arg)
{
	char *const	arguments[] = {
		"number_of_philosophers",
		"time_to_die",
		"time_to_eat",
		"time_to_sleep",
		"number_of_times_each_philosopher_must_eat"
	};

	return (arguments[arg]);
}

t_status	util_atoi(size_t *num, char *str, t_arguments arg)
{
	int	i;

	*num = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		printf("%s cannot be negative\n", get_argument(arg));
		return (FAILURE);
	}
	if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= 48 && str[i] <= 57)
	{
		*num = *num * 10 + str[i] - 48;
		i++;
	}
	if (*num == 0 || *num > __INT_MAX__)
	{
		printf("%s must be an int higher than 0\n", get_argument(arg));
		return (FAILURE);
	}
	return (SUCCESS);
}

void	*util_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (ptr);
	memset(ptr, 0, nmemb * size);
	return (ptr);
}

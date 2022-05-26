/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/27 14:19:15 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/05/22 13:04:38 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <stdio.h>

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

size_t	util_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	util_putstr_fd(const char *s, int fd)
{
	if (!s)
		return (0);
	return (write(fd, s, util_strlen(s)));
}

int	util_putchar_fd(const char c, int fd)
{
	return (write(fd, &c, 1));
}

void	util_putnbr_fd(size_t n, int fd)
{
	if (n >= 10)
		util_putnbr_fd(n / 10, fd);
	util_putchar_fd(n % 10 + 48, fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:25:24 by edlim             #+#    #+#             */
/*   Updated: 2022/05/24 11:25:25 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	checkarg(char **argv)
{
	int	i;
	int	k;

	i = 0;
	while (argv[++i] != NULL)
	{
		k = i;
		if (ft_atoichecker(argv[i]) == 'K')
		{
			write(1, "\033[0;31mError\n", 14);
			return (-1);
		}
	}
	return (0);
}

int	errorhandling(t_array *array, char **argv)
{
	struct timeval	tv;

	if (checkarg(argv) == -1)
		return (-1);
	if (array->philos <= 0)
		return (-1);
	gettimeofday(&tv, NULL);
	if (array->philos == 1)
	{
		printf("\033[0;34m%ld", (tv.tv_sec * 1000) + (tv.tv_usec / 1000));
		printf(" 1 is thinking\n");
		printf("\033[0;31m%ld", (tv.tv_sec * 1000) + (tv.tv_usec / 1000));
		printf(" 1 died\n");
		return (-1);
	}
	return (0);
}

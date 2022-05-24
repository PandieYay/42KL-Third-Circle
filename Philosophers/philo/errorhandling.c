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

int	errorhandling(t_array *array)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (array->philos == 1)
	{
		printf("\033[0;31m%ld", (tv.tv_sec * 1000) + (tv.tv_usec / 1000));
		printf(" 1 died\n");
		return (-1);
	}
	return (0);
}

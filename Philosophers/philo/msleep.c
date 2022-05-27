/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:47:01 by edlim             #+#    #+#             */
/*   Updated: 2022/05/26 14:47:02 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	msleep(int ms, t_array *array)
{
	long	start_time;
	long	current_time;

	gettimeofday(&array->tv, NULL);
	start_time = (array->tv.tv_sec * 1000) + (array->tv.tv_usec / 1000);
	current_time = (array->tv.tv_sec * 1000) + (array->tv.tv_usec / 1000);
	while (current_time - start_time < ms)
	{
		usleep(100);
		gettimeofday(&array->tv, NULL);
		current_time = (array->tv.tv_sec * 1000) + (array->tv.tv_usec / 1000);
	}
}

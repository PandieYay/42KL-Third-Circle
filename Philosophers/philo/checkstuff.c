/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkstuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:59:05 by edlim             #+#    #+#             */
/*   Updated: 2022/06/03 16:59:08 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	checkphilodead(t_philos *philo)
{
	pthread_mutex_lock(&philo->array->lock);
	if (philo->array->philodead == 1)
	{
		pthread_mutex_unlock(&philo->array->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->array->lock);
	return (0);
}

int	checkphiloeat(t_philos *philo)
{
	pthread_mutex_lock(&philo->array->lock);
	if (philo->timesate >= philo->eatnum)
	{
		pthread_mutex_unlock(&philo->array->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->array->lock);
	return (0);
}

int	checkphiloeatall(t_philos *philo, t_array *array)
{
	int	i;
	int	k;

	i = -1;
	k = 0;
	pthread_mutex_lock(&philo->array->lock);
	while (++i < array->philos)
	{
		if (philo->timesate >= philo->eatnum)
			k++;
	}
	if (k == array->philos)
	{
		pthread_mutex_unlock(&philo->array->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->array->lock);
	return (0);
}

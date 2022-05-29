/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfunctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:53:55 by edlim             #+#    #+#             */
/*   Updated: 2022/05/27 13:53:56 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	takeforks(t_philos *philo)
{
	pthread_mutex_lock(&philo->array->lock);
	if (philo->array->philodead == 0)
	{
		gettimeofday(&philo->array->tv, NULL);
		printf("\033[0;36m%ld", (philo->array->tv.tv_sec * 1000)
			+ (philo->array->tv.tv_usec / 1000));
		printf(" %d has taken a fork\n", philo->index + 1);
		printf("\033[0;36m%ld", (philo->array->tv.tv_sec * 1000)
			+ (philo->array->tv.tv_usec / 1000));
		printf(" %d has taken a fork\n", philo->index + 1);
	}
	pthread_mutex_unlock(&philo->array->lock);
}

void	philoeating(t_philos *philo)
{
	pthread_mutex_lock(&philo->array->lock);
	if (philo->array->philodead == 0)
	{
		gettimeofday(&philo->array->tv, NULL);
		philo->lastate = (philo->array->tv.tv_sec * 1000)
			+ (philo->array->tv.tv_usec / 1000);
		printf("\033[0;32m%ld", philo->lastate);
		printf(" %d is eating\n", philo->index + 1);
		++philo->timesate;
	}
	pthread_mutex_unlock(&philo->array->lock);
}

void	philosleep(t_philos *philo)
{
	pthread_mutex_lock(&philo->array->lock);
	if (philo->array->philodead == 0)
	{
		gettimeofday(&philo->array->tv, NULL);
		printf("\033[0;35m%ld", (philo->array->tv.tv_sec * 1000)
			+ (philo->array->tv.tv_usec / 1000));
		printf(" %d is sleeping\n", philo->index + 1);
	}
	pthread_mutex_unlock(&philo->array->lock);
}

void	philothink(t_philos *philo)
{
	pthread_mutex_lock(&philo->array->lock);
	if (philo->array->philodead == 0)
	{
		gettimeofday(&philo->array->tv, NULL);
		printf("\033[0;34m%ld", (philo->array->tv.tv_sec * 1000)
			+ (philo->array->tv.tv_usec / 1000));
		printf(" %d is thinking\n", philo->index + 1);
	}
	pthread_mutex_unlock(&philo->array->lock);
}

void	mutex_forks(t_philos *philo, char c)
{
	if (c == 'L')
	{
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo->next->fork);
	}
	else if (c == 'U')
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
	}
}

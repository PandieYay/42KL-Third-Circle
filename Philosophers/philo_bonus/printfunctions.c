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
	sem_wait(philo->array->lock);
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
	sem_post(philo->array->lock);
}

void	philoeating(t_philos *philo)
{
	sem_wait(philo->array->lock);
	gettimeofday(&philo->array->tv, NULL);
	philo->lastate = (philo->array->tv.tv_sec * 1000)
		+ (philo->array->tv.tv_usec / 1000);
	printf("\033[0;32m%ld", philo->lastate);
	printf(" %d is eating\n", philo->index + 1);
	++philo->timesate;
	sem_post(philo->array->lock);
}

void	philosleep(t_philos *philo)
{
	sem_wait(philo->array->lock);
	if (philo->array->philodead == 0)
	{
		gettimeofday(&philo->array->tv, NULL);
		printf("\033[0;35m%ld", (philo->array->tv.tv_sec * 1000)
			+ (philo->array->tv.tv_usec / 1000));
		printf(" %d is sleeping\n", philo->index + 1);
	}
	sem_post(philo->array->lock);
}

void	philothink(t_philos *philo)
{
	sem_wait(philo->array->lock);
	if (philo->array->philodead == 0)
	{
		gettimeofday(&philo->array->tv, NULL);
		printf("\033[0;34m%ld", (philo->array->tv.tv_sec * 1000)
			+ (philo->array->tv.tv_usec / 1000));
		printf(" %d is thinking\n", philo->index + 1);
	}
	sem_post(philo->array->lock);
}

void	sem_forks(t_philos *philo, char c)
{
	if (c == 'L')
	{
		deathtimer(philo, 'N');
		sem_wait(philo->array->fork);
		sem_wait(philo->array->fork);
		deathtimer(philo, 'N');
	}
	else if (c == 'U')
	{
		sem_post(philo->array->fork);
		sem_post(philo->array->fork);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:00:25 by edlim             #+#    #+#             */
/*   Updated: 2022/05/22 15:00:26 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	deathtimer(t_philos *philo, t_array *array)
{
	int		i;
	long	currentime;

	while (checkphilodead(philo) == 0)
	{
		i = -1;
		while (++i < array->philos)
		{
			pthread_mutex_lock(&array->lock);
			gettimeofday(&array->tv, NULL);
			currentime = (array->tv.tv_sec * 1000)
				+ (array->tv.tv_usec / 1000);
			if (currentime - philo[i].lastate > array->deathtimer
				&& array->philodead == 0)
			{
				printf("\033[0;31m%ld", currentime);
				printf(" %d died\n", philo[i].index + 1);
				philo->array->philodead = 1;
			}
			pthread_mutex_unlock(&philo->array->lock);
		}
	}
}

void	deathtimer2(t_philos *philo, t_array *array)
{
	int		i;
	long	currentime;

	while (checkphilodead(philo) == 0 && checkphiloeatall(philo, array) == 0)
	{
		i = -1;
		while (++i < array->philos)
		{
			if (checkphiloeat(&philo[i]) == 0)
			{
				pthread_mutex_lock(&array->lock);
				gettimeofday(&array->tv, NULL);
				currentime = (array->tv.tv_sec * 1000)
					+ (array->tv.tv_usec / 1000);
				if (currentime - philo[i].lastate > array->deathtimer
					&& array->philodead == 0)
				{
					printf("\033[0;31m%ld", currentime);
					printf(" %d died\n", philo[i].index + 1);
					philo->array->philodead = 1;
				}
				pthread_mutex_unlock(&philo->array->lock);
			}
		}
	}
}

void	*routine(void	*arg)
{
	t_philos	*philo;

	philo = arg;
	while (philo->array->philosinitiated != 1)
		;
	philothink(philo);
	pthread_mutex_lock(&philo->array->lock);
	gettimeofday(&philo->array->tv, NULL);
	philo->lastate = (philo->array->tv.tv_sec * 1000)
		+ (philo->array->tv.tv_usec / 1000);
	pthread_mutex_unlock(&philo->array->lock);
	if ((philo->index + 1) % 2 == 0)
		msleep(50, philo->array);
	while (checkphilodead(philo) == 0)
	{
		mutex_forks(philo, 'L');
		takeforks(philo);
		philoeating(philo);
		msleep(philo->array->eattimer, philo->array);
		philosleep(philo);
		mutex_forks(philo, 'U');
		msleep(philo->array->sleeptimer, philo->array);
		philothink(philo);
	}
	return (NULL);
}

void	*routine2(void	*arg)
{
	t_philos	*philo;

	philo = arg;
	while (philo->array->philosinitiated != 1)
		;
	if ((philo->index + 1) % 2 == 0)
		msleep(50, philo->array);
	gettimeofday(&philo->array->tv, NULL);
	philo->lastate = (philo->array->tv.tv_sec * 1000)
		+ (philo->array->tv.tv_usec / 1000);
	philothink(philo);
	while (checkphilodead(philo) == 0 && philo->timesate < philo->eatnum)
	{
		mutex_forks(philo, 'L');
		takeforks(philo);
		philoeating(philo);
		msleep(philo->array->eattimer, philo->array);
		philosleep(philo);
		mutex_forks(philo, 'U');
		msleep(philo->array->sleeptimer, philo->array);
		philothink(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int			i;
	t_array		array;
	t_philos	*philo;

	if (argc >= 5 && argc <= 6)
		initializevariables(&array, argc, argv);
	else
	{
		write(1, "\033[0;31mError\n", 14);
		return (-1);
	}
	if (errorhandling(&array, argv) == -1)
		return (-1);
	philo = malloc(sizeof(t_philos) * array.philos);
	if (!philo)
		return (-1);
	initializephilos(philo, &array);
	philosophers(philo, &array, argc);
	array.philosinitiated = 1;
	msleep(100, &array);
	initializedeathtimers(philo, &array, argc);
	i = -1;
	while (++i < array.philos)
		pthread_join(philo[i].id, NULL);
	return (0);
}

//tv.tv_sec and tv.tv_usec combine together
//basically problem right now is that mutex fork takes too long
//need thread for deathtimer unless you're smart
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

static int	checkphilodead(t_philos *philo)
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

static void	deathtimer(t_philos *philo)
{
	long	currentime;

	pthread_mutex_lock(&philo->array->lock);
	gettimeofday(&philo->array->tv, NULL);
	currentime = (philo->array->tv.tv_sec * 1000)
		+ (philo->array->tv.tv_usec / 1000);
	if (currentime - philo->lastate > philo->array->deathtimer
		&& philo->array->philodead == 0)
	{
		printf("\033[0;31m%ld", currentime);
		printf(" %d died\n", philo->index + 1);
		philo->array->philodead = 1;
	}
	pthread_mutex_unlock(&philo->array->lock);
}

void	*routine(void	*arg)
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
	while (checkphilodead(philo) == 0)
	{
		mutex_forks(philo, 'L');
		deathtimer(philo);
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
		deathtimer(philo);
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
	i = -1;
	philosophers(philo, &array, argc);
	i = -1;
	array.philosinitiated = 1;
	while (++i < array.philos)
		pthread_join(philo[i].id, NULL);
	return (0);
}

//tv.tv_sec and tv.tv_usec combine together
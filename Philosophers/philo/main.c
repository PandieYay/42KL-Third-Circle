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

static void	initializephilos(t_philos *philo, t_array *array)
{
	int	i;

	i = 0;
	while (i < array->philos)
	{
		gettimeofday(&array->tv, NULL);
		philo[i].sleeptimer = array->sleeptimer;
		philo[i].timesate = 0;
		philo[i].eatnum = array->timesphiloeat;
		philo[i].index = i;
		pthread_mutex_init(&philo[i].fork, NULL);
		philo[i].array = array;
		philo[i].next = &philo[i + 1];
		i++;
	}
	philo[i - 1].next = &philo[0];
}

void	deathtimer(t_philos *philo)
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

static void	*routine(void	*arg)
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
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo->next->fork);
		deathtimer(philo);
		takeforks(philo);
		philoeating(philo);
		msleep(philo->array->eattimer, philo->array);
		philosleep(philo);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		msleep(philo->array->sleeptimer, philo->array);
		philothink(philo);
	}
	return (NULL);
}

static void	*routine2(void	*arg)
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
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo->next->fork);
		deathtimer(philo);
		takeforks(philo);
		philoeating(philo);
		msleep(philo->array->eattimer, philo->array);
		philosleep(philo);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		msleep(philo->array->sleeptimer, philo->array);
		philothink(philo);
	}
	return (NULL);
}

static void	initializevariables(t_array *array, int argc, char **argv)
{
	array->philos = ft_atoi(argv[1]);
	array->philosinitiated = 0;
	array->deathtimer = ft_atoi(argv[2]);
	array->eattimer = ft_atoi(argv[3]);
	array->sleeptimer = ft_atoi(argv[4]);
	array->timesphiloeat = 0;
	array->philomusteat = 0;
	array->philodead = 0;
	pthread_mutex_init(&array->lock, NULL);
	gettimeofday(&array->tv, NULL);
	if (argc == 6)
	{
		array->timesphiloeat = ft_atoi(argv[5]);
		array->philomusteat = 1;
	}
}

int	main(int argc, char **argv)
{
	t_array		array;
	t_philos	*philo;
	int			i;

	if (argc >= 5 && argc <= 6)
		initializevariables(&array, argc, argv);
	else
		return (-1);
	if (errorhandling(&array) == -1)
		return (-1);
	philo = malloc(sizeof(t_philos) * array.philos);
	if (!philo)
		return (-1);
	printf("Philos: %d\n", array.philos);
	initializephilos(philo, &array);
	if (argc == 5)
	{
		i = -1;
		while (++i < array.philos)
			pthread_create(&philo[i].id, NULL, &routine, &philo[i]);
		i = -1;
		array.philosinitiated = 1;
		while (++i < array.philos)
			pthread_join(philo[i].id, NULL);
	}
	else
	{
		i = -1;
		while (++i < array.philos)
			pthread_create(&philo[i].id, NULL, &routine2, &philo[i]);
		i = -1;
		array.philosinitiated = 1;
		while (++i < array.philos)
			pthread_join(philo[i].id, NULL);
	}
	return (0);
}

//tv.tv_sec and tv.tv_usec combine together
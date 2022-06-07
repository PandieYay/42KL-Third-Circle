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

void	*checkallate(void *arg)
{
	int		i;
	t_array	*array;

	array = arg;
	i = -1;
	while (++i < array->philos)
		sem_wait(array->allate);
	sem_post(array->kill);
	return (NULL);
}

static int	checkphiloeat(t_philos *philo)
{
	sem_wait(philo->array->lock);
	if (philo->timesate >= philo->eatnum)
	{
		sem_post(philo->array->lock);
		return (1);
	}
	sem_post(philo->array->lock);
	return (0);
}

void	process(t_philos *philo)
{
	sem_wait(philo->array->sync);
	gettimeofday(&philo->array->tv, NULL);
	philothink(philo);
	philo->lastate = (philo->array->tv.tv_sec * 1000)
		+ (philo->array->tv.tv_usec / 1000);
	while (1)
	{
		sem_forks(philo, 'L');
		takeforks(philo);
		philoeating(philo);
		deathtimer(philo, 'E');
		msleep(philo->array->eattimer, philo->array);
		philosleep(philo);
		sem_forks(philo, 'U');
		deathtimer(philo, 'S');
		msleep(philo->array->sleeptimer, philo->array);
		philothink(philo);
		deathtimer(philo, 'B');
	}
}

void	process2(t_philos *philo)
{
	sem_wait(philo->array->sync);
	gettimeofday(&philo->array->tv, NULL);
	philo->lastate = (philo->array->tv.tv_sec * 1000)
		+ (philo->array->tv.tv_usec / 1000);
	philothink(philo);
	while (checkphiloeat(philo) == 0)
	{
		sem_forks(philo, 'L');
		takeforks(philo);
		philoeating(philo);
		deathtimer(philo, 'E');
		msleep(philo->array->eattimer, philo->array);
		philosleep(philo);
		sem_forks(philo, 'U');
		deathtimer(philo, 'S');
		msleep(philo->array->sleeptimer, philo->array);
		philothink(philo);
		deathtimer(philo, 'B');
	}
	sem_post(philo->array->allate);
}

int	main(int argc, char **argv)
{
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
	sem_wait(array.kill);
	killall(philo, &array);
	return (0);
}
//tv.tv_sec and tv.tv_usec combine together
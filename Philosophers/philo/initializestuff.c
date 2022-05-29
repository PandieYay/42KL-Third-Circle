/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializestuff.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:02:58 by edlim             #+#    #+#             */
/*   Updated: 2022/05/28 16:03:00 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initializephilos(t_philos *philo, t_array *array)
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

void	initializevariables(t_array *array, int argc, char **argv)
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

void	philosophers(t_philos *philo, t_array *array, int argc)
{
	int	i;

	i = -1;
	if (argc == 5)
	{
		while (++i < array->philos)
			pthread_create(&philo[i].id, NULL, &routine, &philo[i]);
	}
	else
	{
		while (++i < array->philos)
			pthread_create(&philo[i].id, NULL, &routine2, &philo[i]);
	}
}

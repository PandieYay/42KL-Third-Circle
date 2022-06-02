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
	sem_unlink("forks");
	sem_unlink("sync");
	sem_unlink("kill");
	sem_unlink("lock");
	array->fork = sem_open("forks", O_CREAT, 0777, array->philos);
	array->sync = sem_open("sync", O_CREAT, 0777, 0);
	array->kill = sem_open("kill", O_CREAT, 0777, 0);
	array->lock = sem_open("lock", O_CREAT, 0777, 1);
	gettimeofday(&array->tv, NULL);
	if (argc == 6)
	{
		array->timesphiloeat = ft_atoi(argv[5]);
		array->philomusteat = 1;
	}
}

int	philosophers(t_philos *philo, t_array *array, int argc)
{
	int	i;

	i = -1;
	while (++i < array->philos)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
			process(&philo[i]);
	}
	i = -1;
	while (++i < array->philos)
		sem_post(array->sync);
	return (0);
}

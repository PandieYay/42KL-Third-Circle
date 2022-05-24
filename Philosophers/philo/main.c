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

static void	*routine(void	*arg)
{
	static int	i = 0;
	t_philos	*philo;

	philo = arg;
	pthread_mutex_lock(&philo->array->lock);
	printf("\033[0;31m%ld", (philo->array->tv.tv_sec * 1000) + (philo->array->tv.tv_usec / 1000));
	printf(" 1 is eating\n");
	if (philo->array->forks >= 2 && i == 0)
	{
		i++;
		philo->deathtimer = philo->array->deathtimer;
		philo->array->forks -= 2;
		usleep(200);
		philo->array->forks += 2;
		philo->deathtimer -= 200;
		printf("%d\n", philo->deathtimer);
	}
	printf("Done eating sir\n");
	pthread_mutex_unlock(&philo->array->lock);
	return (NULL);
}

static void	initializevariables(t_array *array, int argc, char **argv)
{
	array->philos = ft_atoi(argv[1]);
	array->forks = array->philos;
	array->deathtimer = ft_atoi(argv[2]);
	array->eattimer = ft_atoi(argv[3]);
	array->sleeptimer = ft_atoi(argv[4]);
	array->timesphiloeat = 0;
	gettimeofday(&array->tv, NULL);
	if (argc == 6)
		array->timesphiloeat = ft_atoi(argv[5]);
}

int	main(int argc, char **argv)
{
	t_array		array;
	t_philos	*philo;

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
	pthread_mutex_init(&array.lock, NULL);
	if (argc == 5)
	{
		// while (1)
		// {
			int i = 0;
			while (i < array.philos)
			{
				philo[i].array = &array;
				pthread_create(&philo[i].id, NULL, &routine, &philo[i]);
				pthread_join(philo[i].id, NULL);
				i++;
			}
		// }
	}
	pthread_mutex_destroy(&array.lock);
	return (0);
}

//tv.tv_sec and tv.tv_usec combine together
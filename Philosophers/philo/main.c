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
	t_array	*array;

	array = arg;
	pthread_mutex_lock(&array->lock);
	printf("Job has started\n");
	if (array->forks >= 2)
	{
		array->deathtimer = array->oritimer;
		array->forks -= 2;
		usleep(200);
		array->deathtimer -= 2;
		array->forks += 2;
	}
	printf("Job has finished\n");
	pthread_mutex_unlock(&array->lock);
	return (NULL);
}

static void	initializevariables(t_array *array, int argc, char **argv)
{
	array->philos = ft_atoi(argv[1]);
	array->forks = array->philos;
	array->deathtimer = ft_atoi(argv[2]);
	array->oritimer = array->deathtimer;
	array->eattimer = ft_atoi(argv[3]);
	array->sleeptimer = ft_atoi(argv[4]);
	array->timesphiloeat = 0;
	if (argc == 6)
		array->timesphiloeat = ft_atoi(argv[5]);
}

int	main(int argc, char **argv)
{
	t_array			array;
	pthread_t		t1;
	struct timeval	tv;

	if (argc >= 5 && argc <= 6)
		initializevariables(&array, argc, argv);
	else
		return (-1);
	pthread_mutex_init(&array.lock, NULL);
	pthread_create(&t1, NULL, &routine, &array);
	pthread_join(t1, NULL);
	gettimeofday(&tv, NULL);
	printf("\033[1;32mMicroseconds: %d\n", tv.tv_usec);
	pthread_mutex_destroy(&array.lock);
	return (0);
}

//tv.tv_sec and tv.tv_usec combine together
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deathtimers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:24:53 by edlim             #+#    #+#             */
/*   Updated: 2022/06/07 13:24:54 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	deathtimer(t_philos *philo, char c)
{
	long		currentime;

	currentime = get_current_time();
	if (c == 'E')
	{
		if ((currentime - philo->lastate + philo->array->eattimer) 
			> philo->array->deathtimer)
			while ((get_current_time() - philo->lastate) <= philo->array->deathtimer)
				usleep(1);
	}
	else if (c == 'S')
	{
		if ((currentime - philo->lastate + philo->array->sleeptimer) 
			> philo->array->deathtimer)
			while ((get_current_time() - philo->lastate) <= philo->array->deathtimer)
				usleep(1);
	}
	else if (c == 'B')
		if ((currentime - philo->lastate + philo->array->eattimer - philo->array->sleeptimer)
			> philo->array->deathtimer)
			while ((get_current_time() - philo->lastate) <= philo->array->deathtimer)
				usleep(1);
	currentime = get_current_time();
	if ((currentime - philo->lastate) > philo->array->deathtimer)
		{
			sem_wait(philo->array->lock);
			printf("\033[0;31m%ld", currentime);
			printf(" %d died\n", philo->index + 1);
			sem_post(philo->array->kill);
		}
}

void	*deathtimer2(void *arg)
{
	t_philos	*philo;
	long		currentime;

	philo = arg;
	printf("WHY IS THIS RUNNING\n");
	while (1)
	{
		gettimeofday(&philo->array->tv, NULL);
		currentime = (philo->array->tv.tv_sec * 1000)
			+ (philo->array->tv.tv_usec / 1000);
		if ((currentime - philo->lastate) > philo->array->deathtimer)
		{
			sem_wait(philo->array->lock);
			printf("\033[0;31m%ld", currentime);
			printf(" %d died\n", philo->index + 1);
			sem_post(philo->array->lock);
			sem_post(philo->array->kill);
			return (NULL);
		}
	}
}

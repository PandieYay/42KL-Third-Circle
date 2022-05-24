/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:00:52 by edlim             #+#    #+#             */
/*   Updated: 2022/05/22 15:00:53 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_array {
	int				philos;
	int				forks;
	int				deathtimer;
	int				eattimer;
	int				sleeptimer;
	int				timesphiloeat;
	struct timeval	tv;
	pthread_mutex_t	lock;
}	t_array;

typedef struct s_philos {
	int			deathtimer;
	int			sleeptimer;
	int			timesate;
	pthread_t	id;
	t_array		*array;
}	t_philos;

int	ft_atoi(const char *str);
int	errorhandling(t_array *array);

#endif
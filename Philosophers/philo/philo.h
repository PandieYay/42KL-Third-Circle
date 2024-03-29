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
	int				philosinitiated;
	int				philodead;
	int				deathtimer;
	int				eattimer;
	int				sleeptimer;
	int				timesphiloeat;
	int				philomusteat;
	struct timeval	tv;
	pthread_mutex_t	lock;
}	t_array;

typedef struct s_philos {
	long			lastate;
	long			sleeptimer;
	int				timesate;
	int				eatnum;
	int				index;
	pthread_t		id;
	pthread_mutex_t	fork;
	t_array			*array;
	struct s_philos	*next;
}	t_philos;

int		ft_atoi(const char *str);
char	ft_atoichecker(const char *str);
int		errorhandling(t_array *array, char **argv);
void	msleep(int ms, t_array *array);
void	takeforks(t_philos *philo);
void	philoeating(t_philos *philo);
void	philosleep(t_philos *philo);
void	philothink(t_philos *philo);
void	initializevariables(t_array *array, int argc, char **argv);
void	initializephilos(t_philos *philo, t_array *array);
void	mutex_forks(t_philos *philo, char c);
void	philosophers(t_philos *philo, t_array *array, int argc);
void	initializedeathtimers(t_philos *philo, t_array *array, int argc);
void	*routine(void	*arg);
void	*routine2(void	*arg);
void	deathtimer(t_philos *philo, t_array *array);
void	deathtimer2(t_philos *philo, t_array *array);
int		checkphilodead(t_philos *philo);
int		checkphiloeat(t_philos *philo);
int		checkphiloeatall(t_philos *philo, t_array *array);

#endif
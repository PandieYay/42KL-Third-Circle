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
# include <signal.h>
# include <semaphore.h>

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
	sem_t			*sync;
	sem_t			*kill;
	sem_t			*fork;
	sem_t			*lock;
	sem_t			*allate;
}	t_array;

typedef struct s_philos {
	long			lastate;
	long			sleeptimer;
	int				timesate;
	int				eatnum;
	int				index;
	pid_t			pid;
	pthread_t		id;
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
void	sem_forks(t_philos *philo, char c);
void	philosophers(t_philos *philo, t_array *array, int argc);
void	process(t_philos *philo);
void	process2(t_philos *philo);
void	killall(t_philos *philo, t_array *array);
void	deathtimer(t_philos *philo, char c);
void	*deathtimer2(void *arg);
long	get_current_time(void);
void	*checkallate(void *arg);

#endif
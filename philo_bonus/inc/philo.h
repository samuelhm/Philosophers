/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:47:41 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/31 19:53:11 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <semaphore.h>
# include <fcntl.h>

typedef struct s_philo	t_philo;

typedef struct s_table
{
	t_philo			**philos;
	long long		tto_die;
	int				tto_eat;
	int				tto_sleep;
	int				each_eat;
	sem_t			*take_forks_sem;
	sem_t			*forks;
	sem_t			*stop_sem;
	bool			stop;
	long long		reset_time;
}	t_table;

typedef struct s_philo
{
	t_table			*table;
	pthread_t		philo_thrd;
	int				name;
	int				meals;
	sem_t			*last_meal_sem;
	sem_t			*eating_sem;
	bool			is_eating;
	long long		last_meal;
}	t_philo;

//Main_Functions
bool		check_init_args(int argc, char **argv, t_table *table);
void		*routine(void *arg);
void		start_threads(t_table *table);
long long	current_timestamp(void);
int			philo_killer(t_table *table, int i);
void		assign_sem(t_table *table, int i);
void		unlink_philo_sem(int i);

//Philo Actions
void		philo_think(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_eat(t_philo *philo);
void		sleep_precise(long miliseconds);

#endif

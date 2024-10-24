/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:47:41 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/24 18:06:40 by shurtado         ###   ########.fr       */
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
# include <semaphore.h>
# include <stdbool.h>

typedef struct s_philo	t_philo;

typedef struct s_table
{
	t_philo		**philos;
	long long	tto_die;
	int			tto_eat;
	int			tto_sleep;
	int			each_eat;
}	t_table;

typedef struct s_philo
{
	t_table			*table;
	pthread_t		philo_thrd;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	fork;
	int				name;
	int				meals;
	bool			alive;
	pthread_mutex_t	alive_m;
	long long		last_meal;
}	t_philo;

//Main_Functions
bool		check_init_args(int argc, char **argv, t_table *table);
void		set_forks(t_table *table);
void		*routine(void *arg);
void		start_threads(t_table *table);
long long	current_timestamp(void);
void		philo_killer(t_table *table);

//Philo Actions
void		philo_think(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_eat(t_philo *philo);

#endif

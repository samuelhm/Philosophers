/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:47:41 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/24 14:04:04 by shurtado         ###   ########.fr       */
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
	int			tto_die;
	int			tto_eat;
	int			tto_sleep;
	int			each_eat;
}	t_table;

typedef struct s_philo
{
	t_table			*table;
	pthread_t		philo_thrd;
	pthread_mutex_t	mutex;
	bool			*right_fork;
	bool			fork;
	int				name;
	int				meals;
	bool			alive;
	long long		last_meal;
}	t_philo;

//Main_Functions
bool	check_init_args(int argc, char **argv, t_table *table);
void	*routine(void *arg);

//Philo Actions
bool	philo_think(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_eat(t_philo *philo);

#endif

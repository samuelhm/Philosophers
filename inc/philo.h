/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:47:41 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/10 20:23:59 by shurtado         ###   ########.fr       */
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

typedef struct s_philo
{
	t_table			*table;
	pthread_t		philo_thrd;
	pthread_mutex_t	fork;
	pthread_mutex_t	*right_fork;
	int				name;
	int				meals;
	bool			alive;
	long long		last_meal;
}	t_philo;

/*number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]*/

typedef struct s_table
{
	t_philo		*philos;
	int			tto_die;
	int			tto_eat;
	int			tto_sleep;
	int			each_eat;
}	t_table;

//Main_Functions
bool	check_init_args(int argc, char **argv, t_table *table);
void	*routine(void *arg);

//Philo Actions
void	philo_think(int phil_num);
void	philo_sleep(int ms, int phil_num);
void	philo_eat(int ms, pthread_mutex_t *mutex, int phil_num, \
					pthread_mutex_t *mutex2);

#endif

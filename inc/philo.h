/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:47:41 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/09 16:24:16 by shurtado         ###   ########.fr       */
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
	pthread_mutex_t	fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

/*number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]*/

typedef struct s_table
{
	pthread_t	*philo;
	int			tto_die;
	int			tto_eat;
	int			tto_sleep;
	int			each_eat;
}	t_table;

bool	check_init_args(int argc, char **argv, t_table *table);

#endif

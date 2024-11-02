/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:34:14 by shurtado          #+#    #+#             */
/*   Updated: 2024/11/02 19:34:54 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_forks(t_table *table)
{
	int	i;

	i = -1;
	while (table->philos[++i])
	{
		if (table->philos[i + 1])
			table->philos[i]->right_fork = &table->philos[i + 1]->fork;
		else
			table->philos[i]->right_fork = &table->philos[0]->fork;
	}
}

void	start_threads(t_table *table)
{
	int	i;

	i = -1;
	while (table->philos[++i])
	{
		pthread_create(&table->philos[i]->philo_thrd, NULL, \
						routine, table->philos[i]);
		table->philos[i]->last_meal = current_timestamp();
	}
}

static void	unlock_and_gettime(t_table *table, long long *time_now, int i)
{
	pthread_mutex_unlock(&table->stop_m);
	*time_now = current_timestamp();
	pthread_mutex_lock(&table->philos[i]->last_m);
}

static void	killer_func(t_table *table, int i)
{
	pthread_mutex_lock(&table->philos[i]->eating_m);
	if (!table->philos[i]->is_eating)
		kill(table, i);
	pthread_mutex_unlock(&table->philos[i]->eating_m);
	pthread_mutex_unlock(&table->philos[i]->last_m);
}

int	philo_killer(t_table *table, int i)
{
	long long	time_now;

	while (1)
	{
		i = -1;
		while (table->philos[++i])
		{
			pthread_mutex_lock(&table->stop_m);
			if (!table->stop)
			{
				unlock_and_gettime(table, &time_now, i);
				if (time_now - table->philos[i]->last_meal > table->tto_die)
				{
					killer_func(table, i);
					break ;
				}
				else
					pthread_mutex_unlock(&table->philos[i]->last_m);
			}
			else
				return (pthread_mutex_unlock(&table->stop_m));
		}
	}
}

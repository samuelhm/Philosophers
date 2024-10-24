/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:34:14 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/25 00:34:08 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define WAIT 5

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

static void	kill(t_table *table, int i)
{

	if (table->each_eat != table->philos[i]->meals)
		printf("%lld %d died\n", current_timestamp() - table->reset_time, i);
	pthread_mutex_unlock(&table->philos[i]->last_m);
	pthread_mutex_lock(&table->stop_m);
	table->stop = true;
	pthread_mutex_unlock(&table->stop_m);
}

void	philo_killer(t_table *table)
{
	int			i;
	long long	time_now;

	while (1)
	{
		i = -1;
		while (table->philos[++i])
		{
			pthread_mutex_lock(&table->stop_m);
			if (!table->stop)
			{
				pthread_mutex_unlock(&table->stop_m);
				time_now = current_timestamp();
				pthread_mutex_lock(&table->philos[i]->last_m);
				if (time_now - table->philos[i]->last_meal \
					> table->tto_die + WAIT)
				{
					kill(table, i);
					break ;
				}
				else
					pthread_mutex_unlock(&table->philos[i]->last_m);
			}
			else
			{
				pthread_mutex_unlock(&table->stop_m);
				return ;
			}
		}
		usleep(WAIT);
	}
}

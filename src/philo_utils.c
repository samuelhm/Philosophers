/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:34:14 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/24 20:45:18 by shurtado         ###   ########.fr       */
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

static void	kill(t_table *table, int i)
{
	printf("%lld %d died\n", current_timestamp(), i);
	pthread_mutex_lock(&table->stop_m);
	table->stop = true;
	pthread_mutex_unlock(&table->stop_m);
}

void	philo_killer(t_table *table)
{
	int		i;

	while (1)
	{
		i = -1;
		while (table->philos[++i])
		{
			pthread_mutex_lock(&table->stop_m);
			if (!table->stop)
			{
				pthread_mutex_unlock(&table->stop_m);
				pthread_mutex_lock(&table->philos[i]->last_m);
				if (current_timestamp() - table->philos[i]->last_meal \
					>= table->tto_die)
				{
					pthread_mutex_unlock(&table->philos[i]->last_m);
					kill(table, i);
					break ;
				}
				else
					pthread_mutex_unlock(&table->philos[i]->last_m);
			}
			else
				pthread_mutex_unlock(&table->stop_m);
		}
	}
}

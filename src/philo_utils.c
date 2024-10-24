/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:34:14 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/24 18:16:02 by shurtado         ###   ########.fr       */
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
	pthread_mutex_lock(&table->philos[i]->alive_m);
	table->philos[i]->alive = false;
	pthread_mutex_unlock(&table->philos[i]->alive_m);
}

void	philo_killer(t_table *table)
{
	int		i;
	bool	one_alive;

	one_alive = true;
	while (one_alive)
	{
		one_alive = false;
		i = -1;
		while (table->philos[++i])
		{
			if (table->philos[i]->alive)
			{
				if (current_timestamp() - table->philos[i]->last_meal \
					>= table->tto_die)
					kill(table, i);
				else
					one_alive = true;
			}
		}
	}
}

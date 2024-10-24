/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:34:14 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/24 16:32:15 by shurtado         ###   ########.fr       */
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
		pthread_create(&table->philos[i], NULL, routine, table->philos[i]);
	}
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
					table->philos[i]->alive = false;
				else
					one_alive = true;
			}
		}
		if (!one_alive)
			break ;
	}
}

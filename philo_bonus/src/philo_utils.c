/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:34:14 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/28 11:50:58 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_threads(t_table *table)
{
	int	i;

	i = -1;
	while (table->philos[++i])
	{
		pthread_create(&table->philos[i]->philo_thrd, NULL, \
						routine, table->philos[i]);
		table->philos[i]->last_meal = current_timestamp();
		usleep (100);
	}
}

static void	kill(t_table *table, int i)
{
	if (table->each_eat != table->philos[i]->meals)
		printf("%lld %d died\n", current_timestamp() \
				- table->reset_time, i);
	sem_post(table->philos[i]->last_meal_sem);
	sem_wait(table->stop_sem);
	table->stop = true;
	sem_post(table->stop_sem);
}

static void	unlock_and_gettime(t_table *table, long long *time_now, int i)
{
	sem_post(table->stop_sem);
	*time_now = current_timestamp();
	sem_wait(table->philos[i]->last_meal_sem);
}

int	philo_killer(t_table *table, int i)
{
	long long	time_now;

	while (1)
	{
		i = -1;
		while (table->philos[++i])
		{
			sem_wait(table->stop_sem);
			if (!table->stop)
			{
				unlock_and_gettime(table, &time_now, i);
				if (time_now - table->philos[i]->last_meal > \
					table->tto_die)
				{
					kill(table, i);
					break ;
				}
			}
			else
				return (sem_post(table->stop_sem));
			sem_post(table->philos[i]->last_meal_sem);
		}
	}
}

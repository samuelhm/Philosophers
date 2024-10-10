/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:46:41 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/10 20:22:47 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]*/

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (philo->meals < philo->table->each_eat && philo->alive)
	{
		philo_eat(philo->table->tto_eat, &philo->fork, \
					philo->name, philo->right_fork);
		philo->meals++;
		philo_sleep(philo->table->tto_sleep, philo->name);
		philo_think(philo->name);
	}
}

static void	init_table(t_table *table)
{
	table->each_eat = -1;
	table->tto_die = 0;
	table->tto_eat = 0;
	table->tto_sleep = 0;
	table->philos = NULL;
}

int	main(int argc, char *argv[])
{
	t_table	table;

	init_table(&table);
	if (!check_init_args(argc, argv, &table))
	{
		printf("Argumentos invalidos");
		if (table.philos)
			free(table.philos);
		return (1);
	}
	free(table.philos);
	return (0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:46:41 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/24 18:00:20 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]*/

void	*routine(void *arg)
{
	t_philo	*philo;
	bool	alive;

	philo = (t_philo *) arg;
	pthread_mutex_lock(&philo->alive_m);
	alive = philo->alive;
	pthread_mutex_unlock(&philo->alive_m);
	while (alive)
	{
		philo_eat(philo);
		philo->meals++;
		if (philo->meals == philo->table->each_eat || !philo->alive)
			break ;
		philo_sleep(philo);
		philo_think(philo);
		pthread_mutex_lock(&philo->alive_m);
		alive = philo->alive;
		pthread_mutex_unlock(&philo->alive_m);
	}
	return (NULL);
}

static void	init_table(t_table *table)
{
	table->each_eat = -1;
	table->tto_die = 0;
	table->tto_eat = 0;
	table->tto_sleep = 0;
	table->philos = NULL;
}

static void	free_table(t_table *table)
{
	int		i;

	i = -1;
	while (table->philos[++i])
	{
		free(table->philos[i]);
	}
	free (table->philos);
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
	start_threads(&table);
	philo_killer(&table);
	free_table(&table);
	return (0);
}


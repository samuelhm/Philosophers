/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:46:41 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/31 19:52:10 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat] valgrid --tool=helgrind  */

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->right_fork == &philo->fork)
		return (NULL);
	pthread_mutex_lock(&philo->table->stop_m);
	while (!philo->table->stop)
	{
		pthread_mutex_unlock(&philo->table->stop_m);
		philo_eat(philo);
		pthread_mutex_lock(&philo->last_m);
		philo->meals++;
		philo->last_meal = current_timestamp();
		pthread_mutex_unlock(&philo->last_m);
		philo_sleep(philo);
		philo_think(philo);
		pthread_mutex_lock(&philo->table->stop_m);
		if (philo->meals == philo->table->each_eat)
			break ;
	}
	pthread_mutex_unlock(&philo->table->stop_m);
	return (NULL);
}

static void	init_table(t_table *table)
{
	table->each_eat = -1;
	table->tto_die = 0;
	table->tto_eat = 0;
	table->tto_sleep = 0;
	table->philos = NULL;
	table->stop = false;
	table->reset_time = current_timestamp();
	pthread_mutex_init(&table->stop_m, NULL);
}

static void	free_table(t_table *table)
{
	int		i;

	i = -1;
	while (table->philos[++i])
		pthread_join(table->philos[i]->philo_thrd, NULL);
	i = -1;
	while (table->philos[++i])
	{
		pthread_mutex_destroy(&table->philos[i]->fork);
		pthread_mutex_destroy(&table->philos[i]->last_m);
		pthread_mutex_destroy(&table->philos[i]->eating_m);
		free(table->philos[i]);
	}
	pthread_mutex_destroy(&table->stop_m);
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
	philo_killer(&table, -1);
	free_table(&table);
	return (0);
}

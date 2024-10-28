/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:46:41 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/28 12:12:52 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat] valgrid --tool=helgrind  */

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->table->philos[1] == NULL)
		return (NULL);
	sem_wait(philo->table->stop_sem);
	while (!philo->table->stop)
	{
		sem_post(philo->table->stop_sem);
		philo_eat(philo);
		sem_wait(philo->last_meal_sem);
		philo->meals++;
		philo->last_meal = current_timestamp();
		sem_post(philo->last_meal_sem);
		philo_sleep(philo);
		philo_think(philo);
		sem_wait(philo->table->stop_sem);
		if (philo->meals == philo->table->each_eat)
			break ;
	}
	sem_post(philo->table->stop_sem);
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
	table->forks = NULL;
	table->stop_sem = NULL;
	table->take_forks_sem = NULL;
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
		sem_close(table->philos[i]->last_meal_sem);
		sem_destroy(table->philos[i]->last_meal_sem);
		free(table->philos[i]);
	}
	sem_close(table->take_forks_sem);
	sem_destroy(table->take_forks_sem);
	sem_close(table->forks);
	sem_destroy(table->forks);
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

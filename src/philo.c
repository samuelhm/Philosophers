/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:46:41 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/09 18:57:32 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]*/

static void	init_table(t_table *table)
{
	table->each_eat = -1;
	table->tto_die = 0;
	table->tto_eat = 0;
	table->tto_sleep = 0;
	table->philo = NULL;
}

int	main(int argc, char *argv[])
{
	t_table	table;

	init_table(&table);
	if (!check_init_args(argc, argv, &table))
	{
		printf("Argumentos invalidos");
		while (table.philo)
			free(table.philo++);
		return (1);
	}
	while (table.philo)
		free(table.philo++);
	return (0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:15:26 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/24 15:49:35 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_atoi(const char *str)
{
	int	sign;
	int	num;

	sign = 1;
	num = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (num * sign);
}

static void	init_philosophers(t_table *table, int count)
{
	int		i;

	i = -1;
	while (++i < count)
	{
		table->philos[i] = malloc(sizeof(t_philo));
		pthread_mutex_init(&table->philos[i]->fork, NULL);
		table->philos[i]->right_fork = NULL;
		table->philos[i]->table = table;
		table->philos[i]->name = i;
		table->philos[i]->meals = 0;
		table->philos[i]->alive = true;
		table->philos[i]->last_meal = -1;
	}
	set_forks(table);
}

bool	check_init_args(int argc, char **argv, t_table *table)
{
	int	num;

	if (argc < 5 || argc > 6)
		return (false);
	if (argc == 6)
	{
		table->each_eat = ft_atoi(argv[5]);
		if (table->each_eat <= 0)
			return (false);
	}
	table->tto_sleep = ft_atoi(argv[4]);
	table->tto_eat = ft_atoi(argv[3]);
	table->tto_die = ft_atoi(argv[2]);
	num = ft_atoi(argv[1]);
	if (!(table->tto_sleep > 0 && table->tto_eat > 0 && table->tto_die > 0 \
		&& num > 0))
		return (false);
	table->philos = malloc((num + 1) * sizeof(t_philo *));
	table->philos[num] = NULL;
	if (!table->philos)
		return (false);
	init_philosophers(table, num);
	return (true);
}

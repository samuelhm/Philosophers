/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:15:26 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/09 18:56:19 by shurtado         ###   ########.fr       */
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
	table->philo = malloc((num + 1) * sizeof(pthread_t));
	table->philo[num] = 0;
	if (!table->philo)
		return (false);
	return (true);
}

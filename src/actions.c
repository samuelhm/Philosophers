/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:41:34 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/11 18:41:14 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long long	current_timestamp(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (milliseconds);
}

void	philo_sleep(t_philo *philo)
{
	printf ("%lld %d is sleeping\n", current_timestamp(), philo->name);
	usleep(philo->table->tto_sleep);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->fork = false;
	philo->right_fork = false;
	pthread_mutex_unlock(&philo->mutex);
	printf ("%lld %d is eating\n", current_timestamp(), philo->name);
	usleep(philo->table->tto_eat);
}

bool	philo_think(t_philo *philo)
{
	printf ("%lld %d is thinking\n", current_timestamp(), philo->name);
	while (1)
	{
		if ((current_timestamp() - philo->last_meal) > philo->table->tto_die)
		{
			printf("%lld %d died\n", current_timestamp(), philo->name);
			philo->alive = false;
			return (false);
		}
		if (philo->fork && philo->right_fork)
			break ;
	}
	return (true);
}

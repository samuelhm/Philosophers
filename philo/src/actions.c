/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:41:34 by shurtado          #+#    #+#             */
/*   Updated: 2024/11/03 14:37:28 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_fork(pthread_mutex_t *fork, t_philo *philo)
{
	pthread_mutex_lock(fork);
	pthread_mutex_lock(&philo->table->stop_m);
	if (!philo->table->stop)
		printf ("%lld %d taken a fork\n", current_timestamp() - \
				philo->table->reset_time, philo->name);
	pthread_mutex_unlock(&philo->table->stop_m);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->stop_m);
	if (!philo->table->stop)
		printf ("%lld %d is sleeping\n", current_timestamp() - \
				philo->table->reset_time, philo->name);
	pthread_mutex_unlock(&philo->table->stop_m);
	sleep_precise(philo->table->tto_sleep);
}

void	philo_eat(t_philo *philo)
{
	if (&philo->fork < philo->right_fork)
	{
		take_fork(&philo->fork, philo);
		take_fork(philo->right_fork, philo);
	}
	else
	{
		take_fork(philo->right_fork, philo);
		take_fork(&philo->fork, philo);
	}
	pthread_mutex_lock(&philo->eating_m);
	philo->is_eating = true;
	pthread_mutex_unlock(&philo->eating_m);
	pthread_mutex_lock(&philo->last_m);
	philo->meals++;
	philo->last_meal = current_timestamp();
	pthread_mutex_unlock(&philo->last_m);
	pthread_mutex_lock(&philo->table->stop_m);
	if (!philo->table->stop)
		printf ("%lld %d is eating\n", current_timestamp() - \
				philo->table->reset_time, philo->name);
	pthread_mutex_unlock(&philo->table->stop_m);
	sleep_precise(philo->table->tto_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->stop_m);
	if (!philo->table->stop)
		printf ("%lld %d is thinking\n", current_timestamp() - \
				philo->table->reset_time, philo->name);
	pthread_mutex_unlock(&philo->table->stop_m);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:41:34 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/28 12:12:54 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	int	i;

	i = -1;
	sem_wait(philo->table->take_forks_sem);
	while (++i < 2)
	{
		sem_wait(philo->table->forks);
		sem_wait(philo->table->stop_sem);
		if (!philo->table->stop)
			printf ("%lld %d taken a fork\n", current_timestamp() - \
					philo->table->reset_time, philo->name);
		sem_post(philo->table->stop_sem);
	}
	sem_post(philo->table->take_forks_sem);
}

void	philo_sleep(t_philo *philo)
{
	sem_wait(philo->table->stop_sem);
	if (!philo->table->stop)
		printf ("%lld %d is sleeping\n", current_timestamp() - \
				philo->table->reset_time, philo->name);
	sem_post(philo->table->stop_sem);
	sleep_precise(philo->table->tto_sleep);
}

void	philo_eat(t_philo *philo)
{
	take_forks(philo);
	sem_wait(philo->table->stop_sem);
	if (!philo->table->stop)
		printf ("%lld %d is eating\n", current_timestamp() - \
				philo->table->reset_time, philo->name);
	sem_post(philo->table->stop_sem);
	sleep_precise(philo->table->tto_eat);
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}

void	philo_think(t_philo *philo)
{
	sem_wait(philo->table->stop_sem);
	if (!philo->table->stop)
		printf ("%lld %d is thinking\n", current_timestamp() - \
				philo->table->reset_time, philo->name);
	sem_post(philo->table->stop_sem);
}

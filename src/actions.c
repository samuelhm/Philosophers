/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:41:34 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/10 20:31:47 by shurtado         ###   ########.fr       */
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

void	philo_sleep(int ms, int phil_num)
{
	long long	time;

	time = current_timestamp();
	printf ("%d %d is sleeping\n", time, phil_num);
	usleep(ms);
}

void	philo_eat(int ms, pthread_mutex_t *mutex, int phil_num, \
					pthread_mutex_t *mutex2)
{
	long long	time;

	pthread_mutex_lock(mutex);
	pthread_mutex_lock(mutex2);
	time = current_timestamp();
	printf ("%d %d is eating\n", time, phil_num);
	usleep(ms);
	pthread_mutex_unlock(mutex);
	pthread_mutex_unlock(mutex2);
}

void	philo_think(int phil_num)
{
	printf ("%d %d is thinking\n", time, phil_num);
}

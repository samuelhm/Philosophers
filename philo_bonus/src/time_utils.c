/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 02:06:35 by shurtado          #+#    #+#             */
/*   Updated: 2024/11/02 17:37:46 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_timestamp(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (milliseconds);
}

void	sleep_precise(long miliseconds)
{
	long long	start_time;
	long long	elapsed;

	start_time = current_timestamp();
	elapsed = current_timestamp() - start_time;
	while (miliseconds > elapsed)
	{
		usleep(200);
		elapsed = current_timestamp() - start_time;
	}
}

void	assign_sem(t_table **table, int i)
{
	char	last_s_name[12];
	char	eaiting_s_name[13];

	memcpy(last_s_name, "/last_mealx", 12);
	memcpy(eaiting_s_name, "/eating_semx", 13);
	last_s_name[10] = i + '0';
	eaiting_s_name[11] = i + '0';
	(*table)->philos[i]->last_meal_sem = sem_open(last_s_name, \
											O_CREAT, 0644, 1);
	(*table)->philos[i]->eating_sem = sem_open(eaiting_s_name, \
											O_CREAT, 0644, 1);
	if ((*table)->philos[i]->last_meal_sem == SEM_FAILED)
		printf("SEM FAILED LAST MEAL!!");
	if ((*table)->philos[i]->eating_sem == SEM_FAILED)
		printf("SEM FAILED EATING SEM!!");
}

void	unlink_philo_sem(int i)
{
	char	last_s_name[12];
	char	eaiting_s_name[13];

	memcpy(last_s_name, "/last_mealx", 12);
	memcpy(eaiting_s_name, "/eating_semx", 13);
	last_s_name[11] = i + '0';
	eaiting_s_name[12] = i + '0';
	sem_unlink(last_s_name);
	sem_unlink(eaiting_s_name);
}

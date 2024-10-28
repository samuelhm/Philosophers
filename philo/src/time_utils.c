/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 02:06:35 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/28 02:07:05 by shurtado         ###   ########.fr       */
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

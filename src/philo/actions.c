/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:43:28 by pemiguel          #+#    #+#             */
/*   Updated: 2023/02/16 14:22:27 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleepy(t_params *params, int philo)
{
	if (!params->died)
	{
		pthread_mutex_lock(&params->printing);
		printf("%ld %d %s\n", time_diff(time_ms(),
				params->timestamp), philo, SLEEPING);
		pthread_mutex_unlock(&params->printing);
		usleep(params->time_to_sleep * 1000);
	}
	else
		return ;
}

void	act(t_params *params, char *wud, int philo)
{
	if (!params->died)
	{
		pthread_mutex_lock(&params->printing);
		printf("%ld %d %s\n", time_diff(time_ms(),
				params->timestamp), philo, wud);
		pthread_mutex_unlock(&params->printing);
	}
	else
		return ;
}

void	gone(t_params *params, int philo)
{
	pthread_mutex_lock(&params->printing);
	printf("%ld %d %s\n", time_diff(time_ms(), params->timestamp), philo, DIED);
	pthread_mutex_unlock(&params->printing);
}

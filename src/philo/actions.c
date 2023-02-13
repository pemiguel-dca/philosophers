/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:43:28 by pemiguel          #+#    #+#             */
/*   Updated: 2023/02/13 18:08:22 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleepy(t_params *params, int philo)
{
	if (!params->died)
	{
		printf("%ld %d %s\n", time_diff(time_ms(),
				params->timestamp), philo, SLEEPING);
		pthread_mutex_lock(&params->full);
		usleep(params->time_to_sleep * 1000);
		pthread_mutex_unlock(&params->full);
	}
	else
		return ;
}

void	act(t_params *params, char *wud, int philo)
{
	if (!params->died)
		printf("%ld %d %s\n", time_diff(time_ms(),
				params->timestamp), philo, wud);
	else
		return ;
}

void	gone(t_params *params, int philo)
{
	printf("%ld %d %s\n", time_diff(time_ms(), params->timestamp), philo, DIED);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:16:02 by pemiguel          #+#    #+#             */
/*   Updated: 2023/02/09 00:26:10 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_mutex(t_params *params)
{
	int	i;

	i = -1;
	while (++i < params->number_philo)
		if (pthread_mutex_init(&params->forks[i], NULL))
			return (1);
	if (pthread_mutex_init(&params->writing, NULL))
		return (1);
	return (0);
}

int	create_philos(t_params *params)
{
	int i;

	i = -1;
	params->philo = malloc(params->number_philo * sizeof(t_philo));
	while (++i < params->number_philo)
	{
		params->philo[i].x = i + 1;
		params->philo[i].x_ate = 0;
		params->philo[i].left_fork = i;
		params->philo[i].right_fork = (i + 1) % params->number_philo;
		params->philo[i].last_meal = time_ms();
		params->philo[i].params = params;
	}
	return (0);
}

int	create_params(t_params *params, char **argv)
{
	params->number_philo = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	params->wrote = 0;
	if (argv[5])
		params->number_must_eat = ft_atoi(argv[5]);
	else
		params->number_must_eat = -1;
	params->all_ate = 0;
	params->died = 0;
	if (create_mutex(params))
		return (1);
	create_philos(params);
	return (0);
}

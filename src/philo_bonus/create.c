/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:16:02 by pemiguel          #+#    #+#             */
/*   Updated: 2023/02/15 17:45:15 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_sems(t_params *params)
{
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_CHECKING);
	sem_unlink(SEM_SATISFIED);
	params->sem_fork = sem_open(SEM_FORK, O_CREAT, S_IRWXG, params->number_philo / 2);
	if (params->sem_fork == SEM_FAILED)
	{
		printf("Failed to create the semaphore for the forks.\n");
		return (1);
	}
	params->sem_satisfied = sem_open(SEM_SATISFIED, O_CREAT, S_IRWXG, params->number_must_eat);
	params->sem_checking = sem_open(SEM_CHECKING, O_CREAT, S_IRWXG, 1);
	params->sem_eating = sem_open("Eating", O_CREAT, S_IRWXG, 1);
	if (params->sem_satisfied == SEM_FAILED || params->sem_checking == SEM_FAILED)
	{
		printf("Failed to create a semaphore.\n");
		return (1);
	}
	return (0);
}

int	create_philos(t_params *params)
{
	int	i;

	i = -1;
	params->philo = malloc(params->number_philo * sizeof(t_philo));
	while (++i < params->number_philo)
	{
		params->philo[i].x = i + 1;
		params->philo[i].x_ate = 0;
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
	params->satisfied = 0;
	if (argv[5])
		params->number_must_eat = ft_atoi(argv[5]);
	else
		params->number_must_eat = -1;
	params->all_ate = 0;
	params->died = 0;
	if (create_sems(params))
		return (1);
	create_philos(params);
	return (0);
}

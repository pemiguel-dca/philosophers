/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:44:07 by pemiguel          #+#    #+#             */
/*   Updated: 2023/02/17 18:03:23 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eats(t_philo *philo)
{
	t_params	*params;

	params = philo->params;
	pthread_mutex_lock(&(params->fork[philo->left]));
	pthread_mutex_lock(&(params->fork[philo->right]));
	act(params, PICK_UP_FORK, philo->x);
	act(params, PICK_UP_FORK, philo->x);
	act(params, EATING, philo->x);
	pthread_mutex_lock(&params->checking);
	philo->last_meal = time_ms();
	philo->x_ate++;
	pthread_mutex_unlock(&params->checking);
	usleep(params->time_to_eat * 1000);
	pthread_mutex_unlock(&(params->fork[philo->left]));
	pthread_mutex_unlock(&(params->fork[philo->right]));
}

void	*thread(void *philosophers)
{
	t_params	*params;
	t_philo		*philo;

	philo = (t_philo *)philosophers;
	params = philo->params;
	while (!params->died && !params->all_ate
		&& philo->done == 0 && params->number_philo > 1)
	{
		eats(philo);
		sleepy(params, philo->x);
		act(params, THINKING, philo->x);
	}
	return (NULL);
}

void	died(t_params *params, t_philo *philo)
{
	int			i;

	while (!params->all_ate && !params->died)
	{
		i = -1;
		while (++i < params->number_philo)
		{
			pthread_mutex_lock(&params->checking);
			if (time_diff(time_ms(), philo[i].last_meal) > params->time_to_die)
			{
				params->died = 1;
				pthread_mutex_unlock(&params->checking);
				gone(params, philo[i].x);
				return ;
			}
			if (philo[i].x_ate == params->number_must_eat && philo[i].done == 0)
			{
				params->satisfied++;
				philo[i].done++;
			}
			if (params->satisfied == params->number_philo)
					params->all_ate = 1;
			pthread_mutex_unlock(&params->checking);
		}
	}
}

void	exit_p(t_params *params, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < params->number_philo)
		pthread_join(philo[i].thread_x, NULL);
	i = -1;
	while (++i < params->number_philo)
		pthread_mutex_destroy(&(params->fork[i]));
	pthread_mutex_destroy(&(params->checking));
	pthread_mutex_destroy(&(params->printing));
	free(params->philo);
}

int	start(t_params *params)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = params->philo;
	params->timestamp = time_ms();
	while (++i < params->number_philo)
		if (pthread_create(&philo[i].thread_x, NULL, &thread, &philo[i]))
			return (1);
	died(params, philo);
	exit_p(params, philo);
	return (0);
}

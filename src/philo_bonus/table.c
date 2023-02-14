/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:44:07 by pemiguel          #+#    #+#             */
/*   Updated: 2023/02/14 15:12:24 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eats(t_philo *philo)
{
	t_params	*params;

	params = philo->params;
	pthread_mutex_lock(&(params->fork[philo->left]));
	pthread_mutex_lock(&(params->fork[philo->right]));
	act(params, PICK_UP_FORK, philo->x);
	act(params, PICK_UP_FORK, philo->x);
	act(params, EATING, philo->x);
	usleep(params->time_to_eat * 1000);
	philo->last_meal = time_ms();
	philo->x_ate++;
	pthread_mutex_unlock(&(params->fork[philo->left]));
	pthread_mutex_unlock(&(params->fork[philo->right]));
}

void	*thread(void *philosophers)
{
	t_params	*params;
	t_philo		*philo;

	philo = (t_philo *)philosophers;
	params = philo->params;
	while (!params->died && !params->all_ate)
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
				gone(params, philo[i].x);
				params->died = 1;
				return ;
			}
			pthread_mutex_unlock(&params->checking);
			if (philo[i].x_ate == params->number_must_eat)
			{
				pthread_mutex_lock(&params->full);
				params->satisfied++;
				pthread_mutex_unlock(&params->full);
			}
			if (params->satisfied == params->number_philo)
				params->all_ate = 1;
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
	pthread_mutex_destroy(&(params->full));
	pthread_mutex_destroy(&(params->checking));
	free(params->philo);
}

int	create_thread(t_philo	*philo)
{
	pthread_t			thread_x;

	pthread_create(&thread_x, NULL, &thread, &philo);
	pthread_join(thread_x, NULL);
	routine
	died(params, philo);
	exit_p(params, philo);
	return (0);
}

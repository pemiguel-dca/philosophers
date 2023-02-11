/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:44:07 by pemiguel          #+#    #+#             */
/*   Updated: 2023/02/09 00:33:46 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
This function show which philosophers is eating, to eat they need two forks, so
you need to take those to forks out of the table, lock those forks with mutex lock, so that no other one uses it.
It's importante to notice that the philosopher will take is left fork and is right the one on is
index (n_philo) and the one adjacent to him
*/

void	eats(t_philo *philo)
{
	t_params	*params;

	params = philo->params;
	pthread_mutex_lock(&(params->forks[philo->left_fork]));
	pthread_mutex_lock(&(params->forks[philo->right_fork]));
	act(params, PICK_UP_FORK, philo->x);
	act(params, PICK_UP_FORK, philo->x);
	act(params, EATING, philo->x);
	usleep(params->time_to_eat * 1000);
	philo->last_meal = time_ms();
	philo->x_ate++;
	pthread_mutex_unlock(&(params->forks[philo->left_fork]));
	pthread_mutex_unlock(&(params->forks[philo->right_fork]));
}

void	*thread(void *philosophers)
{
	t_params	*params;
	t_philo		*philo;
	static int			done;

	philo = (t_philo *)philosophers;
	params = philo->params;
	done = 0;
	while(!params->died && !params->all_ate)
	{
		eats(philo);
		usleep(100);
		if (!params->all_ate && !done)
		{
			sleepy(params, philo->x);
			act(params, THINKING, philo->x);
		}
		else
		{
			printf("%s",SATISFIED);
			done = 1;
			break ;
		}
	}
	return (NULL);
}

void	died(t_params *params, t_philo *philo)
{
	static int	satisfied = 0;
	int			i;

	satisfied = 0;
	while (!params->all_ate && !params->died)
	{
		i = -1;
		while (++i < params->number_philo)
		{
			if (time_diff(time_ms(), philo[i].last_meal) > params->time_to_die)
			{
				gone(params, philo[i].x);
				params->died = 1;
				return ;
			}
			usleep(100);//bastante importante
			if (philo[i].x_ate == params->number_must_eat)
				satisfied++;
			if (satisfied == params->number_philo)
				params->all_ate = 1;
		}
	}
}

void	exit_p(t_params *params, t_philo *philo)
{
	int i;

	i = -1;
	while (++i < params->number_philo)
		pthread_join(philo[i].thread_x, NULL);
	i = -1;
	while (++i < params->number_philo)
		pthread_mutex_destroy(&(params->forks[i]));
}

int	start(t_params *params)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = params->philo;
	params->timestamp = time_ms();
	while (++i < params->number_philo)
		if (pthread_create(&philo->thread_x, NULL, &thread, &philo[i]))
			return (1);
	died(params, philo);
	exit_p(params, philo);
	return (0);
}

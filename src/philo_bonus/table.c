/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:44:07 by pemiguel          #+#    #+#             */
/*   Updated: 2023/02/16 12:42:50 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eats(t_philo *philo)
{
	t_params	*params;

	params = philo->params;
	sem_wait(params->sem_fork);
	act(params, PICK_UP_FORK, philo->x);
	act(params, PICK_UP_FORK, philo->x);
	act(params, EATING, philo->x);
	usleep(params->time_to_eat * 1000);
	sem_wait(params->sem_checking);
	philo->last_meal = time_ms();
	sem_post(params->sem_checking);
	philo->x_ate++;
	sem_post(params->sem_fork);
}

void	routine(t_philo *philo)
{
	t_params	*params;
	pthread_t	death_thread;

	params = philo->params;
	philo->last_meal = time_ms();
	pthread_create(&death_thread, NULL, &thread_dead, (void *)params);
	while (!params->died && !params->all_ate)
	{
		eats(philo);
		sleepy(params, philo->x);
		act(params, THINKING, philo->x);
	}
	pthread_join(death_thread, NULL);
	if (params->died == 1)
		exit(1);
	exit(0);
}

void	*thread_dead(void *arg)
{
	int			i;
	t_params	*params;

	params = (t_params *)arg;
	while (!params->all_ate && !params->died)
	{
		i = -1;
		while (++i < params->number_philo)
		{
			sem_wait(params->sem_checking);
			if (time_diff(time_ms(), params->philo[i].last_meal) > params->time_to_die)
			{
				gone(params, params->philo[i].x);
				params->died = 1;
				exit (1);
			}
			if (params->philo[i].x_ate == params->number_must_eat)
			{
				params->satisfied++;
				
			}
			if (params->satisfied == params->number_philo)
				params->all_ate = 1;
			sem_post(params->sem_checking);
		}
	}
	return (0);
}

void	exit_p(t_params *params, t_philo *philo)
{
	int	i;
	int	status;

	i = -1;
	while (++i < params->number_philo)
	{
		waitpid(-1 , &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < params->number_philo)
				kill(philo[i].pid, SIGTERM);
		}
	}
	sem_close(params->sem_fork);
	sem_close(params->sem_checking);
	sem_close(params->sem_eating);
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
	{
		philo[i].pid = fork();
		//child
		if (philo[i].pid == 0)
			routine(&philo[i]);
		if (philo[i].pid < 0)
			return (1);
	}
	exit_p(params, philo);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 21:08:11 by pemiguel          #+#    #+#             */
/*   Updated: 2023/02/13 15:28:05 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	confirm_params(char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]))
				return (1);
	}
	i = 0;
	while (argv[++i])
		if (ft_atoi(argv[i]) < 0)
			return (1);
	if (ft_atoi(argv[1]) == 0)
		return (1);
	return (0);
}

void	requirements(void)
{
	printf("Number of inputs -> 5\n");
	printf("There order being respectively: \n[number_of_philosophers");
	printf("(aswell as forks)]\n[time_to_die]\n[time_to_eat]\n");
	printf("[time_to_sleep]\n[number_of_philosophers_that_must_eat]\n");
	printf("⛔ WARNING ⛔\n");
	printf("If any input is nor a digit or an unsigned int, and");
	printf(" number_of_philosophers > 1, you will se this message again :)\n");
}

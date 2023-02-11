/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:34:23 by pemiguel          #+#    #+#             */
/*   Updated: 2023/02/07 14:47:46 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*ARGS:
number_of_philosophers
time_to_die
time_to_eat
time_to_sleep
number_of_times_each_philosopher_must_eat
*/

int	main(int argc, char *argv[])
{
	t_params	params;
	if ((argc == 5 || argc == 6)
		&& !confirm_params(argv)
		&& !create_params(&params, argv))
	{
		if (start(&params))
		{
			printf("error");
			return (0);
		}
	}
	else
		requirements();
	return (0);
}

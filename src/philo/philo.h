/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:34:52 by pemiguel          #+#    #+#             */
/*   Updated: 2023/02/17 17:43:10 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

# define SATISFIED "All philosophers have eaten 😌 \n"
# define PICK_UP_FORK "has taken a fork 🥢"
# define EATING "is eating 🍜"
# define SLEEPING "is sleeping 😴"
# define THINKING "is thinking 🤔"
# define DIED "died 💀"

typedef struct s_params
{
	int					number_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_must_eat;
	int					all_ate;
	int					satisfied;
	int					died;
	suseconds_t			timestamp;
	pthread_mutex_t		fork[250];
	pthread_mutex_t		checking;
	pthread_mutex_t		printing;
	struct s_philo		*philo;

}		t_params;

typedef struct s_philo
{
	int					x;
	int					x_ate;
	int					left;
	int					right;
	int					done;
	suseconds_t			last_meal;
	struct s_params		*params;
	pthread_t			thread_x;
}						t_philo;

//actions
void		sleepy(t_params *params, int philo);
void		act(t_params *params, char *wud, int philo);
void		gone(t_params *params, int philo);

//basics
int			confirm_params(char **argv);
void		requirements(void);

//create
int			create_mutex(t_params *params);
int			create_philos(t_params *params);
int			create_params(t_params *params, char **argv);

//utils
int			ft_atoi(char *str);
int			ft_isdigit(int arg);
suseconds_t	time_diff(int act, int prev);
suseconds_t	time_ms(void);

//table
void		eats(t_philo *philo);
void		*thread(void *philosophers);
void		died(t_params *params, t_philo *philo);
void		exit_p(t_params *params, t_philo *philo);
int			start(t_params *params);

#endif

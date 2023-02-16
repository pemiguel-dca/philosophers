/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:34:52 by pemiguel          #+#    #+#             */
/*   Updated: 2023/02/15 17:29:35 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS__H
# define PHILO_BONUS__H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

# define SEM_SATISFIED "Satisfied"
# define SEM_FORK "Forks"
# define SEM_FULL "Full"
# define SEM_CHECKING "Checking"
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
	sem_t				*sem_satisfied;
	int					died;
	suseconds_t			timestamp;
	sem_t				*sem_fork;
	sem_t				*sem_eating;
	sem_t				*sem_checking;
	struct s_philo		*philo;

}		t_params;

typedef struct s_philo
{
	int					x;
	int					x_ate;
	suseconds_t			last_meal;
	int					pid;
	struct s_params		*params;
}						t_philo;

//actions
void		sleepy(t_params *params, int philo);
void		act(t_params *params, char *wud, int philo);
void		gone(t_params *params, int philo);

//basics
int			confirm_params(char **argv);
void		requirements(void);

//create
int			create_sems(t_params *params);
int			create_philos(t_params *params);
int			create_params(t_params *params, char **argv);

//utils
int			ft_atoi(char *str);
int			ft_isdigit(int arg);
suseconds_t	time_diff(int act, int prev);
suseconds_t	time_ms(void);

//table
void		eats(t_philo *philo);
void		routine(t_philo *philosophers);
void		*thread_dead(void *arg);
void		exit_p(t_params *params, t_philo *philo);
int			start(t_params *params);

#endif

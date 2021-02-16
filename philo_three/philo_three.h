/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:15:25 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/02/16 13:14:45 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <strings.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct			s_arg
{
	unsigned long		num_phi;
	unsigned long		time_die;
	unsigned long		time_eat;
	unsigned long		time_sleep;
	unsigned long		num_eat;
}						t_arg;

typedef struct			s_sem
{
	sem_t				*s_dead;
	sem_t				*s_forks;
	sem_t				*s_stdout;
	sem_t				**s_meals;
	sem_t				*s_time;
	int					*pid;
}						t_sem;

typedef struct			s_monitor
{
	unsigned long		id;
	struct timeval		*time_zero;
	struct timeval		*time_eat;
	t_sem				*data;
}						t_monitor;

t_arg					g_arg;

/*
**  philo_two_utils.c
*/
unsigned long			ft_atoul(char *str);
char					*ft_ultoa(unsigned long n);
void					ft_print_change(unsigned long time,
						unsigned long id, char *str, t_sem *data);

/*
**  philo_two_time.c
*/
unsigned long			ft_get_time(struct timeval *t1,
						struct timeval *t2);
void					ft_init_time(struct timeval **time_add,
						t_monitor *data);

/*
**  philo_two_subroutines.c
*/
void					*ft_new_philosopher(unsigned long id, t_sem *data);

/*
**  philo_two_monitor.c
*/
void					ft_satiated(t_sem *data);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:15:25 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/02/16 12:36:04 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <unistd.h>
# include <strings.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct			s_arg
{
	unsigned long		num_phi;
	unsigned long		time_die;
	unsigned long		time_eat;
	unsigned long		time_sleep;
	unsigned long		num_eat;
	unsigned long		num_satiated;
	int					deadflag;
}						t_arg;

t_arg					g_arg;
char					*g_forks;
unsigned long			g_queue;
pthread_mutex_t			g_m_waiter;
pthread_mutex_t			g_m_stdout;
pthread_mutex_t			g_m_meals;

/*
**  philo_one_utils.c
*/
unsigned long			ft_atoul(char *str);
char					*ft_ultoa(unsigned long n);
void					ft_print_change(unsigned long time,
		unsigned long id, char *str);

/*
**  philo_one_main.c
*/
unsigned long			ft_get_time(struct timeval *t,
		struct timeval *u);

/*
**  philo_one_subroutines.c
*/
void					*ft_new_philosopher(void *philo_id);

#endif

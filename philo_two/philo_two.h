/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:15:25 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/02/15 13:03:17 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <unistd.h>
# include <strings.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct          s_arg
{
    unsigned long       num_phi;
    unsigned long       time_die;
    unsigned long       time_eat;
    unsigned long       time_sleep;
    unsigned long       num_eat;
    unsigned long       num_satiated;
    int                 deadflag;
}                       t_arg;

typedef struct          s_monitor
{
    unsigned long       id;
    struct timeval      *time_zero;
    struct timeval      *time_eat;    
}                       t_monitor;

t_arg                   g_arg;
sem_t                   *gs_forks;
sem_t                   *gs_stdout;
sem_t                   *gs_meals;
sem_t                   *gs_time;

/*
**  philo_two_utils.c 
*/
unsigned long           ft_atoul(char *str);
char                    *ft_ultoa(unsigned long n);
void                    ft_print_change(unsigned long time,
                        unsigned long id, char *str);

/*
**  philo_two_time.c
*/
unsigned long           ft_get_time(struct timeval *t1,
                        struct timeval *t2);
void                    ft_init_time(struct timeval **time_add,
                        t_monitor *data);
void                    ft_usleep(struct timeval *time, unsigned long time_lapse);

/*
**  philo_two_subroutines.c
*/
void                    *ft_new_philosopher(void *philo_id);


#endif
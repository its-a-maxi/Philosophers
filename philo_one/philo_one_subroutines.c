/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one_subroutines.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:23:16 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/02/10 12:14:03 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int              ft_get_fork(unsigned long id, struct timeval *time, int *meals)
{
    unsigned long   left;

    left = (id != 0) ? id - 1 : g_arg.num_phi - 1;
    gettimeofday(time + 2, 0);
    pthread_mutex_lock(&gm_waiter);
    if (ft_can_eat(id, left))
    {
        if (g_queue == id)
            g_queue = g_arg.num_phi;
        g_forks[id] = 0;
        ft_print_change(ft_get_time(time, time + 2), id, "has taken a fork\n");
        g_forks[left] = 0;
        ft_print_change(ft_get_time(time, time + 2), id, "has taken a fork\n");
        pthread_mutex_unlock(&gm_waiter);
        return (1);
    }
    else if ((g_forks[id] && !g_forks[left]) ||
        (!g_forks[id] && g_forks[left]) && (g_queue == g_arg.num_phi)
        && ft_get_time(time + 1, time + 2) > g_arg.time_eat +
        (*meals > 0) * g_arg.time_sleep)
        g_queue = id;
    pthread_mutex_unlock(&gm_waiter);
    return (0);
}

void                    *ft_new_philosopher(void *philo_id)
{
    int                 meals;
    unsigned long       id;
    unsigned long       time_lapse;
    struct timeval      time[3];

    meals = 0;
    id = *(unsigned long *)(&philo_id);
    gettimeofday(time, 0);
    gettimeofday(time + 1, 0);
    gettimeofday(time + 2, 0);
    ft_print_change(ft_get_time(time, time + 2), id, "is thinking\n");
    while (!(g_arg.deadflag) && (g_arg.num_satiated != g_arg.num_phi))
    {
        if (ft_get_fork(id, time, &meals))
            ft_philosophize(id, time, &meals);
        gettimeofday(time + 2, 0);
        if ((time_lapse = ft_get_time(time + 1, time + 2))
            >= g_arg.time_die)
        {
            ft_print_change(time_lapse, id, "died\n");
            g_arg.deadflag = 1;
        }
    }
    return (NULL);
}
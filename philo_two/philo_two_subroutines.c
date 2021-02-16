/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two_subroutines.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:23:16 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/02/15 13:06:56 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void             ft_get_fork(unsigned long id, struct timeval *time)
{
    sem_wait(gs_forks);
    gettimeofday(time + 2, 0);
    ft_print_change(ft_get_time(time, time + 2), id, "has taken a fork\n");
    sem_wait(gs_forks);
    gettimeofday(time + 2, 0);
    ft_print_change(ft_get_time(time, time + 2), id, "has taken a fork\n");
}

static void             ft_philosophize(unsigned long id, struct timeval *time, int *meals)
{
    sem_wait(gs_time);
    gettimeofday(time + 1, 0);
    sem_post(gs_time);
    ft_print_change(ft_get_time(time, time + 1), id, "is eating\n");
    ft_usleep(time, g_arg.time_eat);
    (*meals)++;
    if ((g_arg.num_eat) && (*meals == g_arg.num_eat))
    {
        sem_wait(gs_meals);
        g_arg.num_satiated++;
        sem_post(gs_meals);
    }
    sem_post(gs_forks);
    sem_post(gs_forks);
    gettimeofday(time + 2, 0);
    ft_print_change(ft_get_time(time, time + 2), id, "is sleeping\n");
    ft_usleep(time, g_arg.time_sleep);
    gettimeofday(time + 2, 0);
    ft_print_change(ft_get_time(time, time + 2), id, "is thinking\n");
}

static void             ft_post_all(void)
{
	unsigned long i;

	sem_post(gs_time);
	i = 0;
	while (i < g_arg.num_phi)
	{
		sem_post(gs_forks);
		sem_post(gs_forks);
    }
}

static void             *ft_bury(void *data)
{
	unsigned long	id;
	struct timeval	current_time;
	t_monitor		*monitor_data;

	monitor_data = (t_monitor *)data;
	id = monitor_data->id;
	while (!(g_arg.deadflag) && (g_arg.num_satiated != g_arg.num_phi))
	{
		gettimeofday(&current_time, NULL);
		sem_wait(gs_time);
		if (ft_get_time(monitor_data->time_eat, &current_time)
			> g_arg.time_die)
		{
			ft_print_change(ft_get_time(monitor_data->time_zero, &current_time),
				id, "died\n");
			g_arg.deadflag = 1;
			ft_post_all();
			return (NULL);
		}
		sem_post(gs_time);
	}
	return (NULL);
}

void                    *ft_new_philosopher(void *philo_id)
{
    int                 meals;
    unsigned long       id;
    struct timeval      *time;
    pthread_t           killer;
    t_monitor           data;

    meals = 0;
    id = *(unsigned long *)(&philo_id);
    data.id = id;
    time = malloc(sizeof(struct timeval) * 3);
    ft_init_time(&time, &data);
    pthread_create(&killer, 0, ft_bury, (void *)&data);
    pthread_detach(killer);
    ft_print_change(ft_get_time(time, time + 2), id, "is thinking\n");
    while (!(g_arg.deadflag) && (g_arg.num_satiated != g_arg.num_phi))
    {
        ft_get_fork(id, time);
        ft_philosophize(id, time, &meals);
    }
    free(time);
    pthread_detach(killer);
    return (NULL);
}
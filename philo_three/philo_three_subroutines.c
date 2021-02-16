/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three_subroutines.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:23:16 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/02/16 12:08:10 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void         ft_usleep(struct timeval *time, unsigned long time_lapse)
{
	unsigned long	time_objective;
	unsigned long	current_time;

	gettimeofday(time + 2, 0);
	current_time = ft_get_time(time, time + 2);
	time_objective = current_time + time_lapse;
	while (current_time < time_objective)
	{
		usleep(10);
		gettimeofday(time + 2, 0);
		current_time = ft_get_time(time, time + 2);
	}
}

static void             ft_get_fork(unsigned long id, struct timeval *time, t_sem *data)
{
    sem_wait(data->s_forks);
    gettimeofday(time + 2, 0);
    ft_print_change(ft_get_time(time, time + 2), id, "has taken a fork\n", data);
    sem_wait(data->s_forks);
    gettimeofday(time + 2, 0);
    ft_print_change(ft_get_time(time, time + 2), id, "has taken a fork\n", data);
}

static void             ft_philosophize(unsigned long id, struct timeval *time, int *meals, t_sem *data)
{
    sem_wait(data->s_time);
    gettimeofday(time + 1, 0);
    sem_post(data->s_time);
    ft_print_change(ft_get_time(time, time + 1), id, "is eating\n", data);
    ft_usleep(time, g_arg.time_eat);
    (*meals)++;
    if ((g_arg.num_eat) && (*meals == g_arg.num_eat))
        sem_post(data->s_meals[id]);
    sem_post(data->s_forks);
    sem_post(data->s_forks);
    gettimeofday(time + 2, 0);
    ft_print_change(ft_get_time(time, time + 2), id, "is sleeping\n", data);
    ft_usleep(time, g_arg.time_sleep);
    gettimeofday(time + 2, 0);
    ft_print_change(ft_get_time(time, time + 2), id, "is thinking\n", data);
}

static void             *ft_bury(void *data)
{
	unsigned long	id;
	struct timeval	current_time;
	t_monitor		*m_data;

	m_data = (t_monitor *)data;
	id = m_data->id;
	while (1)
	{
		gettimeofday(&current_time, 0);
		sem_wait(m_data->data->s_time);
		if (ft_get_time(m_data->time_eat, &current_time)
			> g_arg.time_die)
		{
			ft_print_change(ft_get_time(m_data->time_zero, &current_time),
				id, "died\n", m_data->data);
            sem_post(m_data->data->s_dead);
			return (0);
		}
		sem_post(m_data->data->s_time);
	}
}

void                    *ft_new_philosopher(unsigned long id, t_sem *data)
{
    int                 meals;
    struct timeval      *time;
    pthread_t           killer;
    t_monitor           m_data;

    meals = 0;
    m_data.id = id;
    m_data.data = data;
    time = malloc(sizeof(struct timeval) * 3);
    ft_init_time(&time, &m_data);
    pthread_create(&killer, 0, ft_bury, (void *)&m_data);
    pthread_detach(killer);
    ft_print_change(ft_get_time(time, time + 2), id, "is thinking\n", data);
    while (1)
    {
        ft_get_fork(id, time, data);
        ft_philosophize(id, time, &meals, data);
    }
}
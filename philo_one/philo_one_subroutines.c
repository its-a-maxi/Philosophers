/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one_subroutines.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:23:16 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/02/16 12:26:59 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int			ft_can_eat(unsigned long id, unsigned long left)
{
	return ((g_forks[id] == 1) && (g_forks[left] == 1)
			&& ((g_queue == g_arg.num_phi) || (g_queue == id)
			|| ((g_queue > id) && (g_queue - id != 1)
			&& (g_queue - id != g_arg.num_phi - 1)) || ((g_queue < id)
			&& (id - g_queue != 1) && (id - g_queue != g_arg.num_phi - 1))));
}

static int			ft_get_fork(unsigned long id,
					struct timeval *time, int *meals)
{
	unsigned long	left;

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
	else if ((((g_forks[id]) && !g_forks[left]) ||
			((!g_forks[id]) && (g_forks[left]))) && (g_queue == g_arg.num_phi)
			&& ft_get_time(time + 1, time + 2) > g_arg.time_eat +
			(*meals > 0) * g_arg.time_sleep)
		g_queue = id;
	pthread_mutex_unlock(&gm_waiter);
	return (0);
}

static void			ft_usleep(struct timeval *time, unsigned long time_lapse)
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

static void			ft_philosophize(unsigned long id,
					struct timeval *time, int *meals)
{
	unsigned long	left;

	left = (id != 0) ? id - 1 : g_arg.num_phi - 1;
	gettimeofday(time + 1, 0);
	ft_print_change(ft_get_time(time, time + 1), id, "is eating\n");
	ft_usleep(time, g_arg.time_eat);
	pthread_mutex_lock(&gm_waiter);
	g_forks[id] = 1;
	g_forks[left] = 1;
	pthread_mutex_unlock(&gm_waiter);
	(*meals)++;
	if ((g_arg.num_eat) && (*meals == g_arg.num_eat))
	{
		pthread_mutex_lock(&gm_meals);
		g_arg.num_satiated++;
		pthread_mutex_unlock(&gm_meals);
	}
	gettimeofday(time + 2, 0);
	ft_print_change(ft_get_time(time, time + 2), id, "is sleeping\n");
	ft_usleep(time, g_arg.time_sleep);
	gettimeofday(time + 2, 0);
	ft_print_change(ft_get_time(time, time + 2), id, "is thinking\n");
}

void				*ft_new_philosopher(void *philo_id)
{
	int					meals;
	unsigned long		id;
	unsigned long		time_lapse;
	struct timeval		time[3];

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

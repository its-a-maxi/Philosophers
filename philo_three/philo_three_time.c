/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three_time.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:02:50 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/02/16 13:04:05 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

unsigned long	ft_get_time(struct timeval *t1, struct timeval *t2)
{
	return ((unsigned long)((t2->tv_sec - t1->tv_sec) * 1000)
			+ (unsigned long)((t2->tv_usec - t1->tv_usec) / 1000));
}

void			ft_init_time(struct timeval **time, t_monitor *data)
{
	gettimeofday(*time, NULL);
	data->time_zero = *time;
	gettimeofday(*time + 1, NULL);
	data->time_eat = *time + 1;
	gettimeofday(*time + 2, NULL);
}

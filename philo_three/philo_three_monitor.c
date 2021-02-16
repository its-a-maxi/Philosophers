/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three_monitor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:41:36 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/02/15 17:44:43 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void        ft_satiated(t_sem *data)
{
    unsigned long       i;

    i = -1;
    while (++i < g_arg.num_phi)
    {
        if (sem_wait(data->s_meals[i]) == -1)
            exit(1);
    }
    sem_post(data->s_dead);
    exit(0);
}
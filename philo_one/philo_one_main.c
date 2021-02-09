/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:55:31 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/02/09 16:59:16 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int      ft_set_args(int argc, char **argv)
{
    g_arg.num_phi = ft_atoul(argv[1]);
    g_arg.time_die = ft_atoul(argv[2]);
	g_arg.time_eat = ft_atoul(argv[3]);
	g_arg.time_sleep = ft_atoul(argv[4]);
	g_args.num_satiated = 0;
    g_queue = g_arg.num_phi;
    if (argc == 6)
    {
        g_arg.num_eat = ft_atoul(argv[5]);
        return (!(g_arg.num_phil) || !(g_arg.time_die)
            || !(g_arg.time_eat) || !(g_arg.time_sleep)
            || !(g_arg.num_eat));
    }
    else
    {
        g_arg.num_eat = 0;
        return (!(g_arg.num_phil) || !(g_arg.time_die)
            || !(g_arg.time_eat) || !(g_arg.time_sleep));
    }
}

int             main(int argc, char **argv)
{
    unsigned long   i;
    unsigned long   *phi_id;
    pthread_t       *phi_threads;

    if (((argc != 5) && (argc != 6))
        || (ft_set_args(argc, argv))
        || !(m_fork = malloc(sizeof(char) * g_arg.num_phi))
        || !(memset(m_fork, 1, sizeof(char) * g_arg.num_phi))
		|| !(phi_threads = malloc(sizeof(pthread_t) * g_args.num_phi))
		|| !(phi_id = malloc(sizeof(unsigned long) * g_args.num_phi))
		|| (pthread_mutex_init(&m_meals, NULL))
		|| (pthread_mutex_init(&m_waiter, NULL))
		|| (pthread_mutex_init(&m_stdout, NULL))
		|| (create_threads(phi_threads, phi_id)))
		return (1);
}
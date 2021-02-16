/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:55:31 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/02/16 12:36:06 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int		ft_set_args(int argc, char **argv)
{
	g_arg.num_phi = ft_atoul(argv[1]);
	g_arg.time_die = ft_atoul(argv[2]);
	g_arg.time_eat = ft_atoul(argv[3]);
	g_arg.time_sleep = ft_atoul(argv[4]);
	g_arg.num_satiated = 0;
	g_queue = g_arg.num_phi;
	if (argc == 6)
	{
		g_arg.num_eat = ft_atoul(argv[5]);
		return (!(g_arg.num_phi) || !(g_arg.time_die)
				|| !(g_arg.time_eat) || !(g_arg.time_sleep)
				|| !(g_arg.num_eat));
	}
	else
	{
		g_arg.num_eat = 0;
		return (!(g_arg.num_phi) || !(g_arg.time_die)
				|| !(g_arg.time_eat) || !(g_arg.time_sleep));
	}
}

static int		ft_create_threads(pthread_t *phi_threads, unsigned long *phi_id)
{
	unsigned long	i;

	i = -1;
	while (++i < g_arg.num_phi)
	{
		phi_id[i] = i;
		if ((pthread_create(&phi_threads[i], 0, ft_new_philosopher,
						(void *)phi_id[i])))
			return (1);
	}
	return (0);
}

static void		ft_cleaner(unsigned long **id, pthread_t **phi_threads)
{
	pthread_mutex_destroy(&g_m_waiter);
	pthread_mutex_destroy(&g_m_stdout);
	pthread_mutex_destroy(&g_m_meals);
	free(g_forks);
	free(*phi_threads);
	free(*id);
}

unsigned long	ft_get_time(struct timeval *t1, struct timeval *t2)
{
	return ((unsigned long)((t2->tv_sec - t1->tv_sec) * 1000)
			+ (unsigned long)((t2->tv_usec - t1->tv_usec) / 1000));
}

int				main(int argc, char **argv)
{
	unsigned long	i;
	unsigned long	*phi_id;
	pthread_t		*phi_threads;

	if (((argc != 5) && (argc != 6))
			|| (ft_set_args(argc, argv))
			|| !(g_forks = malloc(sizeof(char) * g_arg.num_phi))
			|| !(memset(g_forks, 1, sizeof(char) * g_arg.num_phi))
			|| !(phi_threads = malloc(sizeof(pthread_t) * g_arg.num_phi))
			|| !(phi_id = malloc(sizeof(unsigned long) * g_arg.num_phi))
			|| (pthread_mutex_init(&g_m_meals, NULL))
			|| (pthread_mutex_init(&g_m_waiter, NULL))
			|| (pthread_mutex_init(&g_m_stdout, NULL))
			|| (ft_create_threads(phi_threads, phi_id)))
		return (1);
	i = -1;
	while (++i < g_arg.num_phi)
		pthread_join(phi_threads[i], 0);
	ft_cleaner(&phi_id, &phi_threads);
	return (0);
}

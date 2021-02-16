/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:55:31 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/02/15 17:57:49 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int      ft_set_args(int argc, char **argv)
{
    g_arg.num_phi = ft_atoul(argv[1]);
    if (g_arg.num_phi == 1)
        return (1);
    g_arg.time_die = ft_atoul(argv[2]);
	g_arg.time_eat = ft_atoul(argv[3]);
	g_arg.time_sleep = ft_atoul(argv[4]);
	g_arg.num_satiated = 0;
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

static int      ft_create_threads(pthread_t *phi_threads, unsigned long *phi_id)
{
    int       i;

    if (!(gs_forks = sem_open("forks", O_CREAT, 0664, g_arg.num_phi))
        || !(gs_stdout = sem_open("stdout", O_CREAT, 0664, 1))
        || !(gs_meals = sem_open("meals", O_CREAT, 0664, 1))
        || !(gs_time = sem_open("time", O_CREAT, 0664, 1)))
        return (1);
    i = -1;
    while (++i < g_arg.num_phi)
    {
        phi_id[i] = i;
        if ((pthread_create(&phi_threads[i], 0, ft_new_philosopher,
            (void *)phi_id[i])))
            return (1);
    }
    i = -1;
    while (++i < g_arg.num_phi)
        pthread_join(phi_threads[i], 0);
    return (0);
}

int             main(int argc, char **argv)
{
    unsigned long   *phi_id;
    pthread_t       *phi_threads;

    sem_unlink("forks");
    sem_unlink("stdout");
    sem_unlink("meals");
    sem_unlink("time");
    if (((argc != 5) && (argc != 6))
        || (ft_set_args(argc, argv))
		|| !(phi_threads = malloc(sizeof(pthread_t) * g_arg.num_phi))
		|| !(phi_id = malloc(sizeof(unsigned long) * g_arg.num_phi))
		|| (ft_create_threads(phi_threads, phi_id)))
		return (1);
    free(phi_threads);
    free(phi_id);
    sem_close(gs_forks);
    sem_close(gs_stdout);
    sem_close(gs_meals);
    sem_close(gs_time);
    sem_unlink("forks");
    sem_unlink("stdout");
    sem_unlink("meals");
    sem_unlink("time");
    return (0);
}
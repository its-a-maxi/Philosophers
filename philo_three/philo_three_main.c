/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:55:31 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/02/16 11:59:06 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int      ft_set_args(int argc, char **argv)
{
    g_arg.num_phi = ft_atoul(argv[1]);
    if (g_arg.num_phi == 1)
        return (1);
    g_arg.time_die = ft_atoul(argv[2]);
	g_arg.time_eat = ft_atoul(argv[3]);
	g_arg.time_sleep = ft_atoul(argv[4]);
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

static int		ft_set_data(t_sem *data)
{
	unsigned long	i;
	char			*str;

	if (!(data->s_meals = malloc(sizeof(sem_t *) * g_arg.num_phi)))
		return (1);
	i = 0;
	while (i < g_arg.num_phi)
	{
		str = ft_ultoa(i);
		sem_unlink(str);
		if (!(data->s_meals[i++] = sem_open(str, O_CREAT, 0664, 0)))
			return (1);
		free(str);
	}
	sem_unlink("time");
	sem_unlink("forks");
	sem_unlink("stdout");
	sem_unlink("dead");
	if (!(data->s_dead = sem_open("dead", O_CREAT, 0664, 0))
		|| !(data->s_forks = sem_open("forks", O_CREAT, 0664, g_arg.num_phi))
		|| !(data->s_stdout = sem_open("stdout", O_CREAT, 0664, 1))
		|| !(data->s_time = sem_open("time", O_CREAT, 0664, 1))
		|| !(data->pid = malloc(sizeof(int) * g_arg.num_phi)))
		return (1);
	return (0);
}
static void		ft_birth_child(t_sem *data)
{
	unsigned long	i;
	pid_t			pid;

	i = 0;
	while (i < g_arg.num_phi)
	{
		if (!(data->pid[i] = fork()))
			ft_new_philosopher(i, data);
		else
			++i;
	}
}

static void		ft_destroy_sem(t_sem *data)
{
	unsigned long	i;
	char			*str;

	sem_close(data->s_forks);
	sem_close(data->s_stdout);
	sem_close(data->s_dead);
	sem_close(data->s_time);
	sem_unlink("forks");
	sem_unlink("stdout");
	sem_unlink("dead");
	sem_unlink("time");
	i = 0;
	while (i < g_arg.num_phi)
	{
		str = ft_ultoa(i);
		sem_close(data->s_meals[i++]);
		sem_unlink(str);
		free(str);
	}
}

int             main(int argc, char **argv)
{
    t_sem           data;
    int             pid;
    unsigned long   i;

    if (((argc != 5) && (argc != 6))
        || (ft_set_args(argc, argv))
		|| (ft_set_data(&data)))
		return (1);
    ft_birth_child(&data);
    if (argc == 6)
        if (!(pid = fork()))
            ft_satiated(&data);
    sem_wait(data.s_dead);
    if (argc == 6)
        kill(pid, SIGKILL);
    i = 0;
    while (i < g_arg.num_phi)
        kill(data.pid[i++], SIGKILL);
    free(data.pid);
    ft_destroy_sem(&data);
    free(data.s_meals);
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:36:40 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/02/15 12:09:23 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void         ft_putnbr(char *rst, unsigned long n, int pos)
{
    if (n >= 10)
        ft_putnbr(rst, n / 10, pos - 1);
    rst[pos] = n % 10 + '0';
}

static int		    ft_strlen(char *str)
{
	int		i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
		;
	return (i);
}

char			    *ft_ultoa(unsigned long n)
{
	char			*result;
	int				digit_num;
	unsigned long	temp;

	temp = n;
	digit_num = 1;
	while (temp >= 10)
	{
		temp = temp / 10;
		digit_num++;
	}
	result = malloc(sizeof(char) * (digit_num + 1));
	result[digit_num] = '\0';
	ft_putnbr(result, n, digit_num - 1);
	return (result);
}

unsigned long       ft_atoul(char *str)
{
	unsigned long	result;
	int				i;

	if (!str)
		return (0);
	result = 0;
	i = -1;
	while (str[++i])
	{
		if ((str[i] >= '0') && (str[i] <= '9'))
			result = result * 10 + (str[i] - '0');
		else
			return (0);
	}
	return (result);
}

void                ft_print_change(unsigned long time, unsigned long id, char *str)
{
    char    *time_str;
    char    *id_str;

    if ((g_arg.deadflag) || ((g_arg.num_eat)
	&& (g_arg.num_satiated == g_arg.num_phi)))
        return ;
    time_str = ft_ultoa(time);
    id_str = ft_ultoa(id + 1);
    sem_wait(gs_stdout);
    write(1, time_str, ft_strlen(time_str));
    write(1, " ", 1);
    write(1, id_str, ft_strlen(id_str));
    write(1, " ", 1);
    write(1, str, ft_strlen(str));
    sem_post(gs_stdout);
    free(time_str);
    free(id_str);
}
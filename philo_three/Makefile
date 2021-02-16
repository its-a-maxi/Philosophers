# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/18 17:33:29 by aleon-ca          #+#    #+#              #
#    Updated: 2021/02/15 18:24:13 by mmonroy-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = philo_three_main.c philo_three_subroutines.c philo_three_utils.c philo_three_time.c philo_three_monitor.c

OBJS = $(SRCS:.c=.o)

NAME = philo_three

INCLUDE = -I. -lpthread
#RACE_BUGS = -g -fsanitize=thread
FLAGS = -Werror -Wextra -Wall $(INCLUDE)
GCC = gcc $(FLAGS)

RM = rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
	$(GCC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/18 17:33:29 by aleon-ca          #+#    #+#              #
#    Updated: 2021/02/09 12:37:52 by mmonroy-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = philo_one_main.c philo_one_subroutines.c philo_one_utils.c

OBJS = $(SRCS:.c=.o)

NAME = philo_one

#INCLUDE = -I. -lpthread
#RACE_BUGS = -g -fsanitize=thread
FLAGS = -Werror -Wextra -Wall
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

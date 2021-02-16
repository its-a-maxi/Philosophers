# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/18 17:33:29 by aleon-ca          #+#    #+#              #
#    Updated: 2021/02/15 13:06:13 by mmonroy-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = philo_two_main.c philo_two_subroutines.c philo_two_utils.c philo_two_time.c

OBJS = $(SRCS:.c=.o)

NAME = philo_two

INCLUDE = -I. -lpthread
RACE_BUGS = -g -fsanitize=thread
FLAGS = -Werror -Wextra -Wall $(INCLUDE) $(RACE_BUGS)
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

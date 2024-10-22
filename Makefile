# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: p0ulp1 <p0ulp1@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/17 10:51:21 by phautena          #+#    #+#              #
#    Updated: 2024/10/22 16:56:47 by p0ulp1           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = ./srcs/philo.c ./srcs/dinner.c ./srcs/getters_setters.c ./srcs/init.c ./srcs/parsing.c \
		./srcs/safe_functions.c ./srcs/synchro_utils.c ./srcs/utils.c ./srcs/write.c

OBJS =${SRCS:.c=.o}

CC = cc -Wall -Wextra -Werror -pthread -ggdb -g -I./includes/

.c.o:
	${CC} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${OBJS} -o ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re


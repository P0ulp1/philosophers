# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phautena <phautena@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/17 10:51:21 by phautena          #+#    #+#              #
#    Updated: 2024/10/17 11:15:13 by phautena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = ./srcs/philo.c ./srcs/utils.c

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

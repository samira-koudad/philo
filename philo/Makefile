# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skoudad <skoudad@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/27 19:09:35 by skoudad           #+#    #+#              #
#    Updated: 2025/10/25 05:10:32 by skoudad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Makefile simple
NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
SRCS = src/main.c src/init.c src/utils.c src/routine.c src/monitor.c src/threads.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

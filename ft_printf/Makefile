# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/08 12:48:31 by aumoreno          #+#    #+#              #
#    Updated: 2024/01/13 09:05:02 by aumoreno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra 

SRCS = ft_printf.c ft_put_unsigned.c ft_print_hex.c \
	   ft_print_ptr.c ft_printf_utils.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
			@ar crs $(NAME) $(OBJS)

all : $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 


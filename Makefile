# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/06 18:33:04 by aumoreno          #+#    #+#              #
#    Updated: 2025/01/24 11:57:56 by aumoreno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC = pipex

SRCS = main.c error_utils.c pipe_handler.c pipex_utils.c

LIBFT_PATH = libft/

CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address,leak -g3  -O
RM = rm -f

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(LIBFT_PATH)

OBJS = ${SRCS:.c=.o}

$(EXEC): $(OBJS)
	@make -C $(LIBFT_PATH) --silent
	@$(CC) $(CFLAGS) ${SRCS} -o $(EXEC)  -I./libft -L./libft -lft

all: $(EXEC)

clean:
	@$(RM) $(OBJS)
	@make -C $(LIBFT_PATH) clean --silent

fclean:  clean
	@$(RM) $(EXEC)
	@$(RM) $(OBJS)
	@make -C $(LIBFT_PATH) fclean --silent
	
re: fclean all

.PHONY: all clean fclean re
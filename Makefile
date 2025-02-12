# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/11 09:35:29 by aumoreno          #+#    #+#              #
#    Updated: 2025/02/12 12:13:29 by aumoreno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC = pipex

SRCS = main.c error_utils.c pipe_handler.c pipex_utils.c

LIBFT_PATH = libft/

CC = gcc
CFLAGS = -Wall -Wextra -Werror

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
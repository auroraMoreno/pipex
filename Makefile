# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/06 18:33:04 by aumoreno          #+#    #+#              #
#    Updated: 2025/01/18 11:38:36 by aumoreno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC = pipex

CC = gcc
CFLAGS = -Werror -Wextra -Wall -fsanitize=address,leak -g3

SRCS = main.c error_utils.c gnl/get_next_line_utils.c gnl/get_next_line.c

FT_PRINTF_PATH = ft_printf/
LIBFT_PATH = libft/

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(FT_PRINTF_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(LIBFT_PATH)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)
          
OBJS = $(SRCS:.c=.o)


all : $(EXEC)

$(EXEC): $(OBJS)

$(EXEC): $(OBJS)
	@make -C $(FT_PRINTF_PATH) --silent
	@make -C $(LIBFT_PATH) --silent
	@$(CC) $(CFLAGS) $(SRCS) -o $(EXEC) -I./libft -L./libft -lft -I./ft_printf -L./ft_printf -l ftprintf


clean:
	rm -f $(OBJS)
	@make -C $(FT_PRINTF_PATH) clean --silent

fclean:  clean
	rm -f $(EXEC)
	rm -f $(OBJS)
	@make -C $(FT_PRINTF_PATH) fclean --silent
	@make -C $(LIBFT_PATH) fclean --silent

re: fclean all

.PHONY: all clean fclean re 
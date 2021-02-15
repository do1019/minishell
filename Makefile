# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/14 18:40:41 by dogata            #+#    #+#              #
#    Updated: 2021/02/15 02:13:54 by dogata           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := gcc
CFLAGS := -Wall -Wextra -Werror
INCLUDE := -I./include
LIBS := ar rcs
NAME := minishell
NAME_LIBFT := libft.a
NAME_GNL := get_next_line.a
LIBFT_DIR := libft/
GNL_DIR := get_next_line/

SRCS := srcs/main.c \

OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make bonus -C $(LIBFT_DIR)
	make -C $(GNL_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS) $(LIBFT_DIR)$(NAME_LIBFT) $(GNL_DIR)$(NAME_GNL)

debug: $(NAME)
	@make bonus -C $(LIBFT_DIR)
	make -C $(GNL_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -g  -fsanitize=address -o $(NAME) $(OBJS) $(LIBFT_DIR)$(NAME_LIBFT) $(GNL_DIR)$(NAME_GNL)

clean:
	@rm -f $(OBJS) $(LIBFT_DIR)*.o $(GNL_DIR)*.o

fclean: clean
	@rm -f $(NAME) $(LIBFT_DIR)$(NAME_LIBFT) $(GNL_DIR)$(NAME_GNL)

re: fclean all

.PHONY: all bonus clean fclean re
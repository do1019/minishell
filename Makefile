# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/14 18:40:41 by dogata            #+#    #+#              #
#    Updated: 2021/02/16 00:18:10 by dogata           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := gcc
CFLAGS := -Wall -Wextra -Werror
INCLUDE := -I./include
LIBS := ar rcs
NAME := minishell
NAME_LIBFT := libft.a
LIBFT_DIR := libft/

SRCS := srcs/main.c \

OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make bonus -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS) $(LIBFT_DIR)$(NAME_LIBFT)

debug: $(NAME)
	@make bonus -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -g  -fsanitize=address -o $(NAME) $(OBJS) $(LIBFT_DIR)$(NAME_LIBFT)

clean:
	@rm -f $(OBJS) $(LIBFT_DIR)*.o

fclean: clean
	@rm -f $(NAME) $(LIBFT_DIR)$(NAME_LIBFT)

re: fclean all

.PHONY: all bonus clean fclean re
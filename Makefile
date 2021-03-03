# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/14 18:40:41 by dogata            #+#    #+#              #
#    Updated: 2021/02/28 14:04:25 by dogata           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror
INCLUDE		:= -I./include
LIBS		:= ar rcs
NAME		:= minishell
NAME_LIBFT	:= libft.a
LIBFT_DIR	:= libft/
SRCS		:=	./srcs/main.c \
				./srcs/run_echo.c \
				./srcs/run_env.c \
				./srcs/run_exit.c \
				./srcs/run_pwd.c \
				./srcs/run_cd.c \
				./srcs/run_export.c \
				./srcs/run_unset.c \
				./srcs/export_unset_list.c \
				./srcs/parse_args_semicolon.c \
				./srcs/parse_args_pipeline.c \
				./srcs/parse_args.c \
				./srcs/parse_args_utils.c \
				./srcs/convert_env.c \
				./srcs/create_list.c \
				./srcs/run_redirect.c \
				./srcs/utils.c
OBJS 		:= $(SRCS:.c=.o)

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

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/14 18:40:41 by dogata            #+#    #+#              #
#    Updated: 2021/04/28 18:58:53 by dogata           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror
INCLUDE		:= -I./include
LIBS		:= ar rcs
NAME		:= minishell
NAME_LIBFT	:= libft.a
LIBFT_DIR	:= libft/
SRCS		:=	./srcs/minishell.c \
				./srcs/minishell_loop.c \
				./srcs/minishell_loop_utils.c \
				./srcs/read_command.c \
				./srcs/ms_split_command.c \
				./srcs/ms_split_command_utils.c \
				./srcs/ms_execute_command.c \
				./srcs/ms_launch_command.c \
				./srcs/ms_launch_command_utils.c \
				./srcs/ms_launch_command_utils2.c \
				./srcs/ms_launch_command_utils3.c \
				./srcs/ms_signal_handler.c \
				./srcs/run_echo.c \
				./srcs/run_env.c \
				./srcs/run_exit.c \
				./srcs/run_pwd.c \
				./srcs/run_cd.c \
				./srcs/run_cd_utils.c \
				./srcs/run_export.c \
				./srcs/run_export_utils.c \
				./srcs/run_export_utils2.c \
				./srcs/run_unset.c \
				./srcs/run_unset_utils.c \
				./srcs/run_export_unset_utils.c \
				./srcs/parse_args_semicolon.c \
				./srcs/parse_args_semicolon_utils.c \
				./srcs/parse_args_pipeline.c \
				./srcs/parse_args_pipeline_utils.c \
				./srcs/parse_args.c \
				./srcs/parse_args_utils.c \
				./srcs/parse_args_utils2.c \
				./srcs/free_args_list.c \
				./srcs/check_env.c \
				./srcs/convert_env.c \
				./srcs/convert_non_env.c \
				./srcs/create_list.c \
				./srcs/create_argv.c \
				./srcs/create_free_env_list.c \
				./srcs/sort_env_list.c \
				./srcs/run_redirect.c \
				./srcs/run_redirect_utils.c \
				./srcs/run_redirect_utils2.c \
				./srcs/run_redirect_utils3.c \
				./srcs/run_redirect_builtin_command.c \
				./srcs/convert_lowcase.c \
				./srcs/utils.c \
				./srcs/utils_free.c \
				./srcs/utils_error.c \
				./srcs/utils_error2.c \
				./srcs/push_arrowkey.c \
				./srcs/push_anotherkey.c \
				./srcs/set_fd.c \
				./srcs/edit_env.c
OBJS 		:= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make bonus -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS) $(LIBFT_DIR)$(NAME_LIBFT) -ltermcap

debug: $(NAME)
	@make bonus -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -g  -fsanitize=address -o $(NAME) $(OBJS) $(LIBFT_DIR)$(NAME_LIBFT)

clean:
	@rm -f $(OBJS) $(LIBFT_DIR)*.o

fclean: clean
	@rm -f $(NAME) $(LIBFT_DIR)$(NAME_LIBFT)

re: fclean all

.PHONY: all bonus clean fclean re

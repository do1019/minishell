/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 18:44:22 by dogata            #+#    #+#             */
/*   Updated: 2021/02/16 00:15:03 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>

# define BUFFER_SIZE 1024
# define TOK_BUFFER_SIZE 64
//# define MAX_BUFFER_SIZE 262144
# define TOK_DELIM " \t\r\n\a"

# define ERROR -1

int		run_echo(char **args);
int		run_pwd(char **args);
int		run_env(char **args);
int		run_exit(char **args);

#endif

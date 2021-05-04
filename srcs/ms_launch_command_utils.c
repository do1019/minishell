/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_launch_command_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:32:12 by dogata            #+#    #+#             */
/*   Updated: 2021/04/26 03:24:11 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	void	last_path_creation(t_ms *ms, char **colon,
												char **env_path, int *i)
{
	if (*env_path[0] != '\0')
	{
		ms->paths[(*i)++] = ft_substr(*env_path, 0, *colon - *env_path);
		if (ms->paths[*i - 1] == NULL)
			put_error_exit(NULL);
	}
	if (*env_path[0] == '\0' || *i == 0)
	{
		ms->paths[(*i)++] = ft_strdup("");
		if (ms->paths[*i - 1] == NULL)
			put_error_exit(NULL);
	}
	ms->paths[*i] = NULL;
}

static	void	has_colon_process(t_ms *ms, char **colon,
												char **env_path, int *i)
{
	*colon = ft_strchr(*env_path, ':');
	if (*colon)
	{
		ms->paths[*i] = ft_substr(*env_path, 0, *colon - *env_path);
		if (ms->paths[*i] == NULL)
			put_error_exit(NULL);
		(*i)++;
		*env_path = *colon + 1;
	}
}

static	void	getenv_error_handling(t_ms *ms)
{
	ms->failure_found_env_path_flag = true;
	ms->paths = ft_calloc(sizeof(char *), 2);
	ms->paths[0] = ft_strdup("");
	if (ms->paths[0] == NULL)
		put_error_exit(NULL);
}

static	void	create_env_path_array(t_ms *ms)
{
	char	*env_path;
	char	*colon;
	int		i;

	env_path = getenv("PATH");
	if (env_path == NULL)
		getenv_error_handling(ms);
	else
	{
		ms->paths = ft_calloc(count_colon(env_path) + 2, sizeof(char *));
		if (ms->paths == NULL)
			put_error_exit(NULL);
		i = 0;
		while (1)
		{
			colon = ft_strchr(env_path, ':');
			if (colon)
				has_colon_process(ms, &colon, &env_path, &i);
			else
				break ;
		}
		last_path_creation(ms, &colon, &env_path, &i);
	}
}

void	create_new_args_array_for_execve(t_ms *ms,
											t_args *list, char **args)
{
	int		i;
	int		argc;
	t_args	*current_list;

	i = 0;
	argc = count_array(args);
	ms->new_args = malloc(sizeof(char *) * (argc + 1));
	if (ms->new_args == NULL)
		put_error_exit(NULL);
	current_list = list;
	create_env_path_array(ms);
	while (i < argc)
	{
		if (i == 0 && !ft_strchr (current_list->new_str, '/') && \
											!ms->failure_found_env_path_flag)
			ms->new_args[i] = \
			convert_new_str_for_create_exe_file_path(ms, current_list->new_str);
		else
			ms->new_args[i] = ft_strdup(current_list->new_str);
		if (ms->new_args[i] == NULL)
			put_error_exit(NULL);
		current_list = current_list->next;
		i++;
	}
	ms->new_args[i] = NULL;
}

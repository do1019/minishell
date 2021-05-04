/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_launch_command_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 03:41:22 by dogata            #+#    #+#             */
/*   Updated: 2021/04/30 00:16:15 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	create_exe_file_path(t_ms *ms, char **exe_file, \
												char **exe_file_path, int *i)
{
	char	*file_path;

	*exe_file = ft_strjoin("/", ms->new_args[0]);
	if (exe_file == NULL)
		put_error_exit(NULL);
	if (ms->paths[*i][0] == '\0')
		file_path = ft_strdup(".");
	else
		file_path = ft_strdup(ms->paths[*i]);
	if (file_path == NULL)
		put_error_exit(NULL);
	*exe_file_path = ft_free_strjoin(file_path, *exe_file);
	if (exe_file_path == NULL)
		put_error_exit(NULL);
}

char	*find_executable_file_location(t_ms *ms)
{
	struct stat	stat_buf;
	int			i;

	i = 0;
	if (ms->new_args[0][0] == '\0')
		return (NULL);
	while (ms->paths[i])
	{
		create_exe_file_path(ms, &ms->exe_file, &ms->exe_file_path, &i);
		if (stat(ms->exe_file_path, &stat_buf) != ERROR)
		{
			free_td_array(&ms->paths, free_od_array(&ms->exe_file, 0));
			return (ms->exe_file_path);
		}
		free_od_array(&ms->exe_file, 0);
		free_od_array(&ms->exe_file_path, 0);
		i++;
	}
	free_td_array(&ms->paths, 0);
	return (NULL);
}

char	*find_file_path(t_ms *ms, t_args *list)
{
	char	*return_str;

	if ((ft_strchr(list->new_str, '.') && ft_strchr(list->new_str, '/')) \
										|| ft_strchr(list->new_str, '/'))
		return_str = list->new_str;
	else
		return_str = find_executable_file_location(ms);
	if (return_str == NULL)
	{
		ft_putstr_fd("\x1b[32mminishell: \x1b[m", 2);
		ft_putstr_fd(list->new_str, 2);
		if (ms->failure_found_env_path_flag)
			ft_putendl_fd(": No such file or directory", 2);
		else
			ft_putendl_fd(": command not found", 2);
		exit(COMMAND_NOT_FOUND);
	}
	return (return_str);
}

char	*convert_new_str_for_create_exe_file_path(t_ms *ms,
															char *new_str)
{
	char	**return_str_array;
	char	*return_str;
	int		i;

	ms->has_slash_flag = true;
	return_str_array = ft_split(new_str, '/');
	if (return_str_array == NULL)
		put_error_exit(NULL);
	i = count_array(return_str_array);
	if (i == 0 && return_str_array[0] == NULL)
		return_str = ft_strdup("");
	else
		return_str = ft_strdup(return_str_array[i - 1]);
	if (return_str == NULL)
		put_error_exit(NULL);
	free_td_array(&return_str_array, 0);
	return (return_str);
}

int	count_colon(char *env_path)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (env_path[i])
	{
		if (env_path[i] == ':')
			count++;
		i++;
	}
	return (count);
}

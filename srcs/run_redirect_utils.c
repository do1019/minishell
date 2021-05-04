/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redirect_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikeda <hikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 19:22:03 by hikeda            #+#    #+#             */
/*   Updated: 2021/04/29 13:09:24 by hikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*create_new_command(t_ms *ms, t_args *list, int i)
{
	char		*exe_file_path;
	char		*exe_file;
	struct stat	stat_buf;

	ms->paths = ft_split(getenv("PATH"), ':');
	if (ms->paths == NULL)
		put_error_exit(NULL);
	while (ms->paths[++i])
	{
		exe_file = ft_strjoin("/", list->red_argv[0]);
		if (exe_file == NULL)
			put_error_exit(NULL);
		exe_file_path = ft_strjoin(ms->paths[i], exe_file);
		if (exe_file_path == NULL)
			put_error_exit(NULL);
		if (stat(exe_file_path, &stat_buf) != ERROR)
		{
			free_td_array(&ms->paths, free_od_array(&exe_file, 0));
			return (exe_file_path);
		}
		free_od_array(&exe_file, 0);
		free_od_array(&exe_file_path, 0);
	}
	free_td_array(&ms->paths, 0);
	return (NULL);
}

void	convert_command_name(t_ms *ms, t_args *list)
{
	char	*tmp;

	tmp = list->red_argv[0];
	list->red_argv[0] = create_new_command(ms, list, -1);
	if (list->red_argv[0] == NULL)
	{
		ft_putstr_fd("\x1b[32mminishell: \x1b[m", 2);
		ft_putstr_fd(tmp, 2);
		ft_putendl_fd(": command not found", 2);
		list->red_argv[0] = tmp;
		exit(127);
	}
	free(tmp);
}

void	change_list2(t_args *list, t_args *ptr, int i)
{
	t_args	*tmp;

	ptr = list;
	tmp = NULL;
	while (++i < list->argc - (list->red_num * 2) - 1)
		ptr = ptr->next;
	if (ptr->next != NULL)
		tmp = ptr->next;
	ptr->next = NULL;
	while (tmp != NULL)
	{
		ptr = tmp->next;
		tmp->next = NULL;
		free(tmp->new_str);
		free(tmp);
		tmp = ptr;
	}
	ptr = list;
	i = 0;
	while (ptr != NULL)
	{
		i++;
		ptr = ptr->next;
	}
	list->num = i;
}

void	change_list(t_args *list, t_args *ptr, int i)
{
	int		k;

	k = 1;
	ptr = list;
	while (list->argv[++i])
	{
		if (check_redirect_command(list->argv[i], 0))
		{
			if (k <= list->red_num)
			{
				k++;
				if (list->argv[i + 1] != NULL)
					i++;
			}
			continue ;
		}
		free(ptr->new_str);
		ptr->new_str = ft_strdup(list->argv[i]);
		if (ptr->new_str == NULL)
			put_error_exit(NULL);
		if (ptr->next == NULL)
			duplicate_list(ptr, i - ((k - 1) * 2) - 1);
		ptr = ptr->next;
	}
	change_list2(list, ptr, -1);
}

void	check_consecutive_redirect(t_ms *ms, t_args *list)
{
	int		i;

	ms->exit_code = 0;
	i = -1;
	while (list->argv[++i] && ms->exit_code == 0)
	{
		if (check_redirect_command(list->argv[i], 0))
		{
			if (list->argv[i + 1] == NULL)
				put_syntax_error_redirect(ms);
			else if (check_redirect_command(list->argv[i + 1], 0) > 0)
				put_syntax_error(ms, list->argv[i + 1]);
		}
	}
	if (ms->exit_code != 258)
		check_filename(ms, list);
}

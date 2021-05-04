/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:09:23 by dogata            #+#    #+#             */
/*   Updated: 2021/04/29 17:57:57 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	void	getcwd_error_handling(t_ms *ms, t_args *list)
{
	char	*tmp;
	char	*new_current_dir_path;

	put_error_cd_2(list);
	ms->current_dir_path = ms->tmp_current_dir_path;
	tmp = ft_strjoin("/", list->next->new_str);
	if (tmp == NULL)
		put_error_exit(NULL);
	new_current_dir_path = ft_strjoin(ms->current_dir_path, tmp);
	free_od_array(&tmp, 0);
	if (new_current_dir_path == NULL)
		put_error_exit(NULL);
	edit_environ(ms, "PWD", new_current_dir_path);
	free_od_array(&ms->current_dir_path, 0);
	ms->current_dir_path = new_current_dir_path;
}

static	void	chdir_error_handling_has_argument(t_ms *ms, t_args *list)
{
	if (list->next->new_str[0] != '\0')
		put_error_cd(list);
	ms->exit_code = ERROR_BUILTINS;
}

static	void	run_cd_has_argument(t_ms *ms, t_args *list)
{
	if (chdir(list->next->new_str) == ERROR)
		chdir_error_handling_has_argument(ms, list);
	else
	{
		set_old_pwd_path(ms);
		if (ms->current_dir_path)
		{
			ms->tmp_current_dir_path = ft_strdup(ms->current_dir_path);
			if (ms->tmp_current_dir_path == NULL)
				put_error_exit(NULL);
			free(ms->current_dir_path);
		}
		ms->current_dir_path = getcwd(NULL, 0);
		if (ms->current_dir_path == NULL)
		{
			getcwd_error_handling(ms, list);
			return ;
		}
		else
			free_od_array(&ms->tmp_current_dir_path, 0);
		edit_environ(ms, "PWD", ms->current_dir_path);
	}
}

static	void	chdir_error_handling_without_argument(t_ms *ms)
{
	edit_environ(ms, "OLDPWD", ms->tmp_old_pwd_path);
	ft_putendl_fd("\x1b[32mminishell: \x1b[mcd : HOME not set", 2);
	ms->exit_code = ERROR_BUILTINS;
}

int	run_cd(t_ms *ms, t_args *list, char **args)
{
	extern char	**environ;
	int			i;

	i = 0;
	ms->exit_code = EXIT_SUCCESS;
	if (args[1] == NULL)
	{
		while (environ[i] != NULL)
		{
			if (!ft_strncmp(environ[i], "HOME=", 5))
				break ;
			i++;
		}
		set_old_pwd_path(ms);
		if (chdir(environ[i] + 5) == ERROR)
			chdir_error_handling_without_argument(ms);
		else
			edit_environ(ms, "PWD", environ[i] + 5);
	}
	else
		run_cd_has_argument(ms, list);
	return (ms->exit_code);
}

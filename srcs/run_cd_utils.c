/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 05:54:54 by dogata            #+#    #+#             */
/*   Updated: 2021/04/29 17:46:31 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	put_error_cd_2(t_args *list)
{
	int	errnum;

	errnum = errno;
	ft_putstr_fd(list->new_str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
	ft_putendl_fd(strerror(errnum), 2);
}

void	put_error_cd(t_args *list)
{
	int	errnum;

	errnum = errno;
	ft_putstr_fd("\x1b[32mminishell: \x1b[m", 2);
	ft_putstr_fd(list->new_str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(list->next->new_str, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errnum), 2);
}

void	after_once_additional_old_pwd_path(t_ms *ms, char *rt)
{
	if (rt == NULL)
		execution_minishell_once("export OLDPWD=");
	else if (!ft_memcmp(rt, "", 1))
	{
		edit_environ(ms, "PWD", ms->current_dir_path);
		edit_environ(ms, "OLDPWD", "");
	}
	else
		edit_environ(ms, "OLDPWD", ms->current_dir_path);
}

void	add_old_pwd_key(char *old_pwd_value)
{
	char	*old_pwd;
	char	*command;

	old_pwd = ft_strjoin_clip_equal("OLDPWD", old_pwd_value);
	if (old_pwd == NULL)
		put_error_exit(NULL);
	command = ft_strjoin("export ", old_pwd);
	if (command == NULL)
		put_error_exit(NULL);
	execution_minishell_once(command);
	free_od_array(&old_pwd, 0);
	free_od_array(&command, 0);
}

void	set_old_pwd_path(t_ms *ms)
{
	extern char	**environ;
	char		*rt;

	rt = getenv("PWD");
	ms->tmp_old_pwd_path = getenv("OLDPWD");
	if (ms->add_old_pwd_flag == false)
	{
		if (rt == NULL)
		{
			create_env_var_list(ms, environ);
			ms->env_lst_front = ms->env_lst;
			if (is_env_var_name_duplicated(ms, "PWD", ms->env_var_count))
				add_old_pwd_key(ms->current_dir_path);
			else
				add_old_pwd_key("");
			ft_lstclear_ms(&(ms->env_lst_front));
		}
		else if (!ft_memcmp(rt, "", 1))
			add_old_pwd_key("");
		else
			add_old_pwd_key(ms->current_dir_path);
		ms->add_old_pwd_flag = true;
	}
	else
		after_once_additional_old_pwd_path(ms, rt);
}

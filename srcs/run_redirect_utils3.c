/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redirect_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikeda <hikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:00:26 by hikeda            #+#    #+#             */
/*   Updated: 2021/04/28 20:51:20 by hikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_filename_quate_backslash(t_ms *ms, t_args *list, int i, int j)
{
	if (j == 0)
		ms->back_slash_flag = false;
	else if (j >= 1 && list->filename[i][j - 1] == '\\'
			&& ms->back_slash_flag == false && ms->single_quate_flag == false)
		ms->back_slash_flag = true;
	else if (j >= 1 && list->filename[i][j - 1] == '\\'
			&& ms->back_slash_flag == 1 && ms->single_quate_flag == false)
		ms->back_slash_flag = false;
	else
		ms->back_slash_flag = false;
	if (ms->single_quate_flag == false && ms->double_quate_flag == false
		&& ms->back_slash_flag == false && list->filename[i][j] == '\'')
		ms->single_quate_flag = true;
	else if (ms->single_quate_flag == false && ms->double_quate_flag == false
		&& ms->back_slash_flag == false && list->filename[i][j] == '\"')
		ms->double_quate_flag = true;
	else if (ms->single_quate_flag == true && ms->double_quate_flag == false
		&& ms->back_slash_flag == false && list->filename[i][j] == '\'')
		ms->single_quate_flag = false;
	else if (ms->single_quate_flag == false && ms->double_quate_flag == true
		&& ms->back_slash_flag == false && list->filename[i][j] == '\"')
		ms->single_quate_flag = false;
}

void	check_filename_env4(t_ms *ms, t_args *list, char *env, int len)
{
	int		i;
	int		count;
	int		flag;

	i = 0;
	count = 0;
	flag = 0;
	while (env[len + i] != '\0' && ms->double_quate_flag == false)
	{
		while (env[len + i] != '\0' && env[len + i] == ' ')
		{
			flag = 0;
			i++;
		}
		while (env[len + i] != '\0' && env[len + i] != ' ')
		{
			flag = 1;
			i++;
		}
		if (flag)
			count++;
		flag = 0;
	}
	if (count > 1)
		put_ambiguous_error(ms, list->filename[ms->fnc]);
}

void	check_filename_env3(t_ms *ms, t_args *list, int e_posi, int env_strlen)
{
	char		*ptr;
	int			i;
	extern char	**environ;

	ptr = (char *)malloc(sizeof(char) * (env_strlen + 1));
	if (ptr == NULL)
		put_error_exit(NULL);
	i = -1;
	while (++i < env_strlen)
		ptr[i] = list->filename[ms->fnc][e_posi + i];
	i = -1;
	while (environ[++i])
	{
		if ((ft_strncmp(ptr, environ[i], env_strlen)) == 0)
		{
			if (ft_strchar_num(environ[i], '=') == env_strlen)
			{
				check_filename_env4(ms, list, environ[i], env_strlen + 1);
				ms->fnp += env_strlen - 1;
			}
		}
	}
	free(ptr);
}	

void	check_filename_env2(t_ms *ms, t_args *list, int i, int j)
{
	int		k;

	k = 1;
	while (list->filename[i][j + k] != '$' && list->filename[i][j + k] != '\0'
		&& list->filename[i][j + k] != '\'' && list->filename[i][j + k] != '\"'
		&& list->filename[i][j + k] != '\\' && list->filename[i][j + k] != ' '
		&& list->filename[i][j + k] != '-' && list->filename[i][j + k] != '%'
		&& list->filename[i][j + k] != '^' && list->filename[i][j + k] != '='
		&& list->filename[i][j + k] != '~' && list->filename[i][j + k] != ']'
		&& list->filename[i][j + k] != '}' && list->filename[i][j + k] != ':'
		&& list->filename[i][j + k] != '+' && list->filename[i][j + k] != ','
		&& list->filename[i][j + k] != '.' && list->filename[i][j + k] != '/'
		&& list->filename[i][j + k] != '?' && list->filename[i][j + k] != '!'
		&& list->filename[i][j + k] != '#' && list->filename[i][j + k] != '`'
		&& list->filename[i][j + k] != '{' && list->filename[i][j + k] != '['
		&& list->filename[i][j + k] != '(' && list->filename[i][j + k] != ')')
		k++;
	check_filename_env3(ms, list, j + 1, k - 1);
	if (list->filename[i][j + 1] == '$')
		ms->fnp++;
}

void	check_filename_env(t_ms *ms, t_args *list)
{
	ms->single_quate_flag = false;
	ms->double_quate_flag = false;
	ms->fnc = -1;
	while (list->filename[++ms->fnc] != NULL && ms->exit_code == 0)
	{
		ms->fnp = -1;
		while (list->filename[ms->fnc][++ms->fnp] && ms->exit_code == 0)
		{
			check_filename_quate_backslash(ms, list, ms->fnc, ms->fnp);
			if (ms->single_quate_flag != true && ms->back_slash_flag == false
				&& list->filename[ms->fnc][ms->fnp] == '$')
				check_filename_env2(ms, list, ms->fnc, ms->fnp);
		}
	}
}

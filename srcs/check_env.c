/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikeda <hikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:19:22 by hikeda            #+#    #+#             */
/*   Updated: 2021/04/27 13:50:59 by hikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strchar_num(char *environ, int c)
{
	int		i;

	i = 0;
	while (environ[i] != '\0')
	{
		if (environ[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	check_quate_backslash(t_ms *ms, int i)
{
	if (i == 0)
		ms->back_slash_flag = false;
	else if (i >= 1 && ms->line[i - 1] == '\\'
		&& ms->back_slash_flag == false && ms->single_quate_flag == false)
		ms->back_slash_flag = true;
	else if (i >= 1 && ms->line[i - 1] == '\\'
		&& ms->back_slash_flag == 1 && ms->single_quate_flag == false)
		ms->back_slash_flag = false;
	else
		ms->back_slash_flag = false;
	if (ms->single_quate_flag == false && ms->double_quate_flag == false
		&& ms->back_slash_flag == false && ms->line[i] == '\'')
		ms->single_quate_flag = true;
	else if (ms->single_quate_flag == false && ms->double_quate_flag == false
		&& ms->back_slash_flag == false && ms->line[i] == '\"')
		ms->double_quate_flag = true;
	else if (ms->single_quate_flag == true && ms->double_quate_flag == false
		&& ms->back_slash_flag == false && ms->line[i] == '\'')
		ms->single_quate_flag = false;
	else if (ms->single_quate_flag == false && ms->double_quate_flag == true
		&& ms->back_slash_flag == false && ms->line[i] == '\"')
		ms->single_quate_flag = false;
}

int	check_env3(t_ms *ms, int e_posi, int env_strlen, int env_flag)
{
	char		*ptr;
	int			i;
	extern char	**environ;

	ptr = (char *)malloc(sizeof(char) * (env_strlen + 1));
	if (ptr == NULL)
		put_error_exit(NULL);
	i = -1;
	while (++i < env_strlen)
		ptr[i] = ms->line[e_posi + i];
	i = -1;
	while (environ[++i])
	{
		if ((ft_strncmp(ptr, environ[i], env_strlen)) == 0)
		{
			if (ft_strchar_num(environ[i], '=') == env_strlen)
			{
				convert_env(ms, environ[i], e_posi, env_strlen);
				env_flag = 2;
			}
		}
	}
	free(ptr);
	return (env_flag);
}

void	check_env2(t_ms *ms, int i)
{
	int		j;
	int		env_flag;

	j = 1;
	env_flag = 1;
	while (ms->line[i + j] != '$' && ms->line[i + j] != '\0'
		&& ms->line[i + j] != '\'' && ms->line[i + j] != '\"'
		&& ms->line[i + j] != '\\' && ms->line[i + j] != ' '
		&& ms->line[i + j] != '-' && ms->line[i + j] != '%'
		&& ms->line[i + j] != '^' && ms->line[i + j] != '='
		&& ms->line[i + j] != '~' && ms->line[i + j] != ']'
		&& ms->line[i + j] != '}' && ms->line[i + j] != ':'
		&& ms->line[i + j] != '+' && ms->line[i + j] != ','
		&& ms->line[i + j] != '.' && ms->line[i + j] != '/'
		&& ms->line[i + j] != '?' && ms->line[i + j] != '!'
		&& ms->line[i + j] != '#' && ms->line[i + j] != '`'
		&& ms->line[i + j] != '{' && ms->line[i + j] != '['
		&& ms->line[i + j] != '(' && ms->line[i + j] != ')')
		j++;
	env_flag = check_env3(ms, i + 1, j - 1, env_flag);
	if (env_flag == 1)
		check_non_env(ms, i + 1);
}

void	check_env1(t_ms *ms)
{
	ms->new_line = (char *)malloc(sizeof(char)
			* ((int)ft_strlen(ms->line) + 1));
	if (ms->new_line == NULL)
		put_error_exit(NULL);
	ms->single_quate_flag = false;
	ms->double_quate_flag = false;
	ms->back_slash_flag = false;
	ms->lp = -1;
	ms->nlp = 0;
	while (ms->line[++ms->lp])
	{
		check_quate_backslash(ms, ms->lp);
		if (ms->single_quate_flag != true && ms->line[ms->lp] == '$'
			&& ms->back_slash_flag == false)
			check_env2(ms, ms->lp);
		else
			ms->new_line[ms->nlp++] = ms->line[ms->lp];
	}
	ms->new_line[ms->nlp] = '\0';
	ms->line = ms->new_line;
}

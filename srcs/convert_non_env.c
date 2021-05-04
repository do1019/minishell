/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_non_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 18:17:31 by hikeda            #+#    #+#             */
/*   Updated: 2021/04/27 13:30:59 by hikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	convert_non_env1(t_ms *ms, char *s1, char *s2)
{
	int		s1_len;
	int		i;
	char	*ptr;

	s1_len = ft_strlen(s1);
	ptr = (char *)malloc(sizeof(char) * (ms->nlp + s1_len + ft_strlen(s2) + 1));
	if (ptr == NULL)
		put_error_exit(NULL);
	i = -1;
	while (++i < ms->nlp)
		ptr[i] = ms->new_line[i];
	i = -1;
	while (++i < s1_len)
		ptr[ms->nlp + i] = s1[i];
	free(ms->new_line);
	ms->new_line = ptr;
	ms->lp += 1;
	ms->nlp += s1_len;
}

void	convert_non_env2(t_ms *ms, char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != '$' && str[i] != '\''
		&& str[i] != '\"' && str[i] != '\\' && str[i] != ' '
		&& str[i] != '-')
		i++;
	ms->lp += i + 1;
}

void	convert_non_env3(t_ms *ms, int e_posi, int i, int j)
{
	int		ptr_len;
	char	*ptr;
	char	*num;

	num = ft_itoa(ms->exit_code);
	ptr = ms->new_line;
	ptr_len = ms->nlp + ft_strlen(ms->line + e_posi) + ft_strlen(num);
	ms->new_line = (char *)malloc(sizeof(char) * (ptr_len + 1));
	if (ms->new_line == NULL)
		put_error_exit(NULL);
	while (++i < ms->nlp)
		ms->new_line[i] = ptr[i];
	while (num[++j])
		ms->new_line[i + j] = num[j];
	ms->lp += 1;
	ms->nlp += ft_strlen(num);
	free(ptr);
	free(num);
}

void	check_non_env2(t_ms *ms, int e_posi)
{
	if (ms->line[e_posi - 1] == '$' && ms->line[e_posi] == '?')
		convert_non_env3(ms, e_posi, -1, -1);
	else if (ms->line[e_posi - 1] == '$' && ((ms->line[e_posi] == '%')
			|| (ms->line[e_posi] == '^') || (ms->line[e_posi] == '=')
			|| (ms->line[e_posi] == '~') || (ms->line[e_posi] == ']')
			|| (ms->line[e_posi] == '}') || (ms->line[e_posi] == ':')
			|| (ms->line[e_posi] == '+') || (ms->line[e_posi] == ',')
			|| (ms->line[e_posi] == '.') || (ms->line[e_posi] == '/')
			|| (ms->line[e_posi] == '|') || (ms->line[e_posi] == ';')
			|| (ms->line[e_posi] == '[') || (ms->line[e_posi] == '{')
			|| (ms->line[e_posi] == '(') || (ms->line[e_posi] == ')')
			|| (ms->line[e_posi] == '!') || (ms->line[e_posi] == '&')))
	{
		ms->new_line[ms->nlp++] = ms->line[ms->lp++];
		ms->new_line[ms->nlp++] = ms->line[ms->lp];
	}
}

void	check_non_env(t_ms *ms, int e_posi)
{
	if (ms->line[e_posi - 1] == '$' && (ms->line[e_posi] == '\0'
			|| ms->line[e_posi] == ' ' || ms->line[e_posi] == '\\'
			|| (ms->line[e_posi] == '\"' && ms->double_quate_flag == true)))
		ms->new_line[ms->nlp++] = '$';
	else if (ms->line[e_posi - 1] == '$' && ms->line[e_posi] == '0')
		convert_non_env1(ms, "bash", ms->line + e_posi + 1);
	else if (ms->line[e_posi - 1] == '$' && (ms->line[e_posi] == '@'
			|| ms->line[e_posi] == '*' || ft_isdigit(ms->line[e_posi])))
		ms->lp += 1;
	else if (ms->line[e_posi - 1] == '$' && ms->line[e_posi] == '-')
		convert_non_env1(ms, "himBH", ms->line + e_posi + 1);
	else if (ms->line[e_posi - 1] == '$' && ms->line[e_posi] == '#')
		convert_non_env1(ms, "0", ms->line + e_posi + 1);
	else if (ms->line[e_posi - 1] == '$' && ms->line[e_posi] == '$')
		convert_non_env1(ms, "PID", ms->line + e_posi + 1);
	else if (ms->line[e_posi - 1] == '$'
		&& (ms->line[e_posi] == '_' || ft_isalpha(ms->line[e_posi])))
		convert_non_env2(ms, ms->line + e_posi + 1);
	else
		check_non_env2(ms, e_posi);
}

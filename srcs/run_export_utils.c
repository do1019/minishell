/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_export_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:09:50 by dogata            #+#    #+#             */
/*   Updated: 2021/04/28 22:09:36 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	duplicate_env_to_tmp_env(t_ms *ms, char **env, int *count)
{
	*count = 0;
	while (*count < ms->env_var_count)
	{
		ms->tmp_env[*count] = ft_strdup(env[*count]);
		if (ms->tmp_env[*count] == NULL)
			put_error_exit(NULL);
		(*count)++;
	}
}

int	is_valid_export_argument(t_ms *ms, char *arg)
{
	int	i;

	i = 0;
	ms->equal_flag = false;
	if (arg[0] == '\0')
		return (ERROR);
	while (arg[i])
	{
		if (i == 0 && !ft_isalpha(arg[i]) && arg[i] != '_')
			return (ERROR);
		if (i > 0 && !ft_isalnum(arg[i]) && arg[i] != '=' && \
								!ms->equal_flag && arg[i] != '_')
			return (ERROR);
		if (arg[i] == '=')
			ms->equal_flag = true;
		i++;
	}
	return (0);
}

int	is_env_var_name_duplicated(t_ms *ms, char *arg, int env_var_num)
{
	int			i;
	int			args_var_len;
	t_env_list	*current_content;

	i = 0;
	ms->empty_value = false;
	ms->env_lst = ms->env_lst_front;
	div_at_equal(ms, arg);
	args_var_len = ft_strlen(ms->div[0]);
	while (i < env_var_num)
	{
		current_content = ms->env_lst->content;
		if (!ft_memcmp(ms->div[0], current_content->var_name, args_var_len + 1))
		{
			if (ms->div[1] == NULL)
				ms->empty_value = true;
			return (free_td_array(&ms->div, i));
		}
		ms->env_lst = ms->env_lst->next;
		i++;
	}
	return (free_td_array(&ms->div, 0));
}

void	check_duplicate_and_add_env_var(t_ms *ms, int *count)
{
	int	rt;

	if (ms->converted_new_str)
		free_od_array(&ms->converted_new_str, 0);
	ms->converted_new_str = \
		convert_new_str_for_escape_sequence(ms->current_list->new_str);
	rt = is_env_var_name_duplicated(ms, \
						ms->current_list->new_str, ms->env_var_count);
	if (rt != 0 && !ms->empty_value)
	{
		free(ms->tmp_env[rt]);
		ms->tmp_env[rt] = ft_strdup(ms->converted_new_str);
		if (ms->tmp_env[rt] == NULL)
			put_error_exit(NULL);
	}
	else if (rt == 0 && !ms->empty_value)
	{
		ms->tmp_env[*count] = ft_strdup(ms->converted_new_str);
		if (ms->tmp_env[*count] == NULL)
			put_error_exit(NULL);
		(*count)++;
	}
}

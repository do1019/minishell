/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 02:53:38 by dogata            #+#    #+#             */
/*   Updated: 2021/04/28 20:12:20 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\a')
		return (true);
	return (false);
}

int	count_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

void	execution_minishell_once(char *read_command)
{
	t_ms	tmp_ms;
	t_args	tmp_list;

	minishell_pre_init(&tmp_ms);
	tmp_ms.line = ft_strdup(read_command);
	if (tmp_ms.line == NULL)
		put_error_exit(NULL);
	tmp_ms.main_loop_count = 1;
	execution_minishell_process(&tmp_ms, &tmp_list);
	free(tmp_ms.current_dir_path);
	free_od_array(&(tmp_ms.line), 0);
}

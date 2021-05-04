/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redirect_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikeda <hikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:00:26 by hikeda            #+#    #+#             */
/*   Updated: 2021/04/27 16:23:20 by hikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	create_filename(t_ms *ms, t_args *list, int i, int j)
{
	int		argc;
	int		flag;

	flag = 0;
	argc = 0;
	while (ms->old_line[i] != '\0')
	{
		flag = check_redirect_command(ms->old_line, i);
		while (flag == 0 && ms->old_line[i] != '\0')
			flag = check_redirect_command(ms->old_line, ++i);
		if (ms->old_line[i] != '\0')
		{
			i += flag;
			while (ms->old_line[i] == ' ')
				i++;
			while (ms->old_line[i + j] != ' ' && ms->old_line[i + j] != '\0'
				&& check_redirect_command(ms->old_line, i + j) == 0)
				j++;
			list->filename[argc++] = ft_strndup(ms->old_line + i, j);
			i += j;
			j = 0;
		}
	}
}

void	check_filename(t_ms *ms, t_args *list)
{
	int		i;

	list->filename = (char **)malloc(sizeof(char *) * (list->red_num + 1));
	if (list->filename == NULL)
		put_error_exit(NULL);
	create_filename(ms, list, 0, 0);
	list->filename[list->red_num] = NULL;
	check_filename_env(ms, list);
	i = 0;
	while (list->filename[i] != NULL)
		free(list->filename[i++]);
	free(list->filename);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:02:24 by dogata            #+#    #+#             */
/*   Updated: 2021/04/29 13:10:05 by hikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minishell_init(t_ms *ms)
{
	ms->line_length = 0;
	g_signal_flags &= \
		~(SIGNAL_PIPELINE_FLAG | SIGNAL_FORK_FLAG | \
			SIGNAL_RESET_LINE_FLAG | SIGNAL_NEWLINE_FLAG);
	ms->main_loop_count = 0;
	ms->exec_count = 0;
	ms->sc_splited_count = 0;
	ms->semicolon_num = 0;
	ms->semicolon_flag = false;
	ms->pipeline_flag = false;
	ms->array_count = 0;
	ms->start = 0;
	ms->c = 0;
	ms->builtin_command_flag = false;
	ms->converted_new_str = NULL;
	ms->failure_found_env_path_flag = false;
	ms->has_slash_flag = false;
}

static	void	parse_and_execute_command(t_ms *ms, t_args *list, char *line)
{
	ms->old_line = ms->line;
	if (ft_strchr(line, '$'))
		check_env1(ms);
	split_command(ms, ms->line);
	parse_args(ms, list, ms->args);
	if (list->red_err == 0)
		execute_command(ms, list, ms->args);
	else
		put_syntax_error_redirect(ms);
	if (ft_strchr(ms->old_line, '$'))
		free(ms->old_line);
	free_redirect_argv(list);
	free_args_list(list);
	free_td_array(&ms->args, 0);
}

static	void	execution_pipeline_process(t_ms *ms, t_args *list)
{
	while (ms->exec_count < ms->pl_splited_count)
	{
		free_od_array(&ms->line, 0);
		ms->line = ft_strdup(ms->pl_splited_line[ms->exec_count]);
		if (ms->line == NULL)
			put_error_exit(NULL);
		parse_and_execute_command(ms, list, ms->line);
	}
	free_td_array(&ms->pl_splited_line, 0);
	ms->pipeline_flag = false;
}

void	execution_minishell_process(t_ms *ms, t_args *list)
{
	int	i;

	i = 0;
	while (i < ms->main_loop_count)
	{
		if (ms->semicolon_flag == true)
		{
			free_od_array(&ms->line, 0);
			ms->line = ft_strdup(ms->sc_splited_line[i]);
			if (ms->line == NULL)
				put_error_exit(NULL);
		}
		split_command_line_with_pipeline(ms, ms->line);
		if (ms->pipeline_flag == true)
			execution_pipeline_process(ms, list);
		else
			parse_and_execute_command(ms, list, ms->line);
		i++;
	}
}

void	minishell_loop(t_ms *ms, t_args *list)
{
	while (1)
	{
		minishell_init(ms);
		if (!read_command_loop(ms))
			continue ;
		if (split_command_line_with_semicolon(ms) == ERROR)
			continue ;
		if (is_valid_pipeline_with_correct_syntax(ms) == ERROR)
			continue ;
		execution_minishell_process(ms, list);
		free_lines(ms);
	}
}

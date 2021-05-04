/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_launch_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:13:04 by dogata            #+#    #+#             */
/*   Updated: 2021/04/28 01:41:31 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	void	parent_process(t_ms *ms)
{
	close_prev_pipe_fd(ms);
	if (ms->pipeline_flag == true)
	{
		ms->prev_pipe_fd[READ] = ms->current_pipe_fd[READ];
		ms->prev_pipe_fd[WRITE] = ms->current_pipe_fd[WRITE];
	}
	if (ms->pipeline_flag == true && ms->exec_count == ms->pipeline_num)
	{
		ms->wpid = waitpid(ms->pid, &ms->wpid_status, WUNTRACED);
		if (ms->wpid == ERROR)
			put_error_rt(ms, ERROR);
		else
			ms->exit_code = WEXITSTATUS(ms->wpid_status);
		while (wait(NULL) > 0)
			;
	}
	else if (ms->pipeline_flag == false)
	{
		ms->wpid = waitpid(ms->pid, &ms->wpid_status, WUNTRACED);
		if (ms->wpid == ERROR)
			put_error_rt(ms, ERROR);
		else
			ms->exit_code = WEXITSTATUS(ms->wpid_status);
	}
	signal_handler_in_launch(ms);
}

static	void	child_pipeline_process(t_ms *ms)
{
	if (ms->exec_count == 0)
		close_and_dup_write(ms);
	else if (ms->exec_count > 0 && ms->exec_count != ms->pipeline_num)
	{
		close_and_dup_read(ms);
		close_and_dup_write(ms);
	}
	else
		close_and_dup_read(ms);
}

static	void	child_process(t_ms *ms, t_args *list, char **args, char **env)
{
	char	*file_path;

	if (ms->pipeline_flag == true)
		child_pipeline_process(ms);
	if (ms->builtin_command_flag == false && ms->redirect_flag == false)
	{
		create_new_args_array_for_execve(ms, list, args);
		file_path = find_file_path(ms, list);
	}
	if (ms->builtin_command_flag == true || ms->redirect_flag == true)
	{
		execute_buildin_command(ms, list, args);
		exit(ms->exit_code);
	}
	else if (execve(file_path, ms->new_args, env) == ERROR)
		put_error_exit_for_execve(list->new_str);
}

static	int	fork_error_handling(t_ms *ms)
{
	if (ms->pipeline_flag == true)
	{
		close(ms->current_pipe_fd[READ]);
		close(ms->current_pipe_fd[WRITE]);
		close(ms->prev_pipe_fd[READ]);
		close(ms->prev_pipe_fd[WRITE]);
	}
	return (put_error_rt(ms, ERROR));
}

int	launch_command(t_ms *ms, t_args *list, char **args)
{
	extern char	**environ;
	char		**env;

	env = environ;
	if (ms->pipeline_flag == true)
		g_signal_flags |= SIGNAL_PIPELINE_FLAG;
	if (ms->pipeline_flag == true && ms->exec_count != ms->pipeline_num)
	{
		if (pipe(ms->current_pipe_fd) == ERROR)
			return (put_error_rt(ms, ERROR));
	}
	ms->pid = fork();
	if (ms->pid == ERROR)
		return (fork_error_handling(ms));
	ms->wpid_status = 0;
	g_signal_flags |= SIGNAL_FORK_FLAG;
	if (ms->pid == 0)
		child_process(ms, list, args, env);
	else
		parent_process(ms);
	g_signal_flags &= ~(SIGNAL_PIPELINE_FLAG | SIGNAL_FORK_FLAG);
	if (ms->pipeline_flag == true)
		ms->exec_count++;
	return (1);
}

#include "../include/minishell.h"

static volatile sig_atomic_t fork_flag;

int		launch(t_ms *ms, char **args)
{
	int		status;
	//extern char **environ;

	// パイプを生成
	if (ms->pipeline_flag == true && ms->start_pipe_process == false)
	{
		if (pipe(ms->current_pipe_fd) < 0)
			put_error_rt(); //返すのか返さないのか
	}
	//子プロセスを生成　成功した場合PID、失敗した場合-1が返る。
	if ((ms->pid = fork()) < 0)
	{
		if (ms->pipeline_flag == true)
		{
			close(ms->current_pipe_fd[READ]);
			close(ms->current_pipe_fd[WRITE]);
		}
		put_error_rt();
	}
	status = 0;
	fork_flag = true;
	//子プロセス
	if (ms->pid == 0)
	{
		if (ms->start_pipe_process == true)
		{
			close(ms->prev_pipe_fd[WRITE]);
			dup2(ms->prev_pipe_fd[READ], 0);
			close(ms->prev_pipe_fd[READ]);
		}
		if (ms->pipeline_flag == true)
		{
			//子のreadを閉じる
			close(ms->current_pipe_fd[READ]);
			// 子の標準出力を親の標準出力につなぐ
			dup2(ms->current_pipe_fd[WRITE], 1);
			// 割り当てたファイルディスクリプタは閉じる
			close(ms->current_pipe_fd[WRITE]);
		}
		//printf("chiled: ok from child\n");
		if (execvp(args[0], args) == ERROR)
			put_error();
		exit(EXIT_FAILURE);
	}
	//親プロセス
	else
	{
		if (ms->start_pipe_process == true)
		{
			close(ms->prev_pipe_fd[READ]);
			close(ms->prev_pipe_fd[WRITE]);
		}
		if (ms->pipeline_flag == true)
		{

			ms->prev_pipe_fd[READ] = ms->current_pipe_fd[READ];
			ms->prev_pipe_fd[WRITE] = ms->current_pipe_fd[WRITE];
			ms->start_pipe_process = true; //?
			// ms->fd_read = pipe_child2parent[READ];
			// ms->fd_write = pipe_parent2child[WRITE];
		}
		//子プロセスの終了or状態変化待ち
		if ((ms->wpid = waitpid(ms->pid, &status, WUNTRACED)) < 0)
			put_error_rt();
		if (status == SIGINT)
			ft_putendl_fd("", 1);
		if (status == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 1);
		//printf("status = [%d]\n", status);
		//printf("parent: child process pid = %d\n", ms->pid);
		// while (WIFEXITED(status) && !WIFSIGNALED(status))
		// 	ms->wpid = waitpid(pid, &status, WUNTRACED);
	}
	fork_flag = false;
	return (1);
}

int		execute(t_ms *ms, str_list *list, char **args)
{
	if (args[0] == NULL)
		return (1);
	if (ms->redirect_flag == true)
		return (run_redirect(list));
	else if (ft_strcmp(list->new_str, "echo") == 0)
		return (run_echo(list));
	else if (ft_strcmp(list->new_str, "pwd") == 0)
		return (run_pwd());
	else if (ft_strcmp(list->new_str, "env") == 0)
		return (run_env());
	else if (ft_strcmp(list->new_str, "exit") == 0)
		return (run_exit(list));
	else if (ft_strcmp(list->new_str, "cd") == 0)
		return (run_cd(args));
	else if (ft_strcmp(list->new_str, "export") == 0)
		return (run_export(args));
	else if (ft_strcmp(list->new_str, "unset") == 0)
		return (run_unset(args));
	return (launch(ms, args));
}

char	**split_command(char *line)
{
	int		buffer_size;
	int		position;
	char	**tokens;
	char	*token;

	buffer_size = BUFFER_SIZE;
	position = 0;
	if (!(tokens = malloc(sizeof(char *) * buffer_size)))
		put_error_exit();
	token = strtok(line, TOK_DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;
		if (position >= buffer_size)
		{
			buffer_size += TOK_BUFFER_SIZE;
			tokens = realloc(tokens, buffer_size * sizeof(char *));
			if (!tokens)
				put_error_exit();
		}
		token = strtok(NULL, TOK_DELIM);
	}
	tokens[position] = NULL;
	return (tokens);
}

char	*read_command_line(t_ms *ms)
{
	char	*buffer;
	char	*line;
	int		rt;

	//ms->loop_count = 0;
	(void)ms;
	if (!(line = ft_calloc(1, sizeof(char))))
		return (put_error_free(NULL));
	if (!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (put_error_free(&line));
	while (1)
	{
		if ((rt = read(0, buffer, BUFFER_SIZE)) == ERROR)
			return (put_error_free(&line));
		//CTRL-D exit
		if (rt == 0 && line[0] == '\0')
		{
			ft_putendl_fd("exit", 1);
			exit(EXIT_SUCCESS);
		}
		else if (rt == 0 && line[0] != '\0')
			continue;
		//CTRL-D
		if (buffer[rt - 1] != '\n')
		{
			buffer[rt] = '\0';
			if (!(line = ft_free_strjoin(line, buffer)))
				return (put_error_free(&buffer));
			continue;
		}
		buffer[rt - 1] = '\0';
		if (!(line = ft_free_strjoin(line, buffer)))
			return (put_error_free(&buffer));
		if ((rt - 1) <= BUFFER_SIZE) //?
			break;
	}
	// if (ms->loop_count > 256)
	// {
	// 	ft_putendl_fd("minishell: Argument list too long", 2);
	// 	free(buffer);
	// 	free(line);
	// 	exit(EXIT_FAILURE);
	// }
	free(buffer);
	return (line);
}

void	minishell_loop(t_ms *ms, str_list *list)
{
	char	*line;
	char	**args;
	int		i;
	int		j;
	int		status;

	//statusが止まる＝minishellのループが止まる場合はある？(exit以外で)
	status = 1;
	while (status)
	{
		ft_putstr_fd("\x1b[32mminishell: \x1b[m", 1);
		if (!(line = read_command_line(ms)))
			continue;
		if (split_command_line_with_semicolon(ms, line) == ERROR)
			continue;
		if (is_valid_pipeline_with_correct_syntax(ms, line) == ERROR)
			continue;
		if (ms->semicolon_flag == true)
		{
			i = 0;
			while (i < ms->sc_splited_count && status)
			{
				if (ms->pipeline_flag == true)
				{
					if (split_command_line_with_pipeline(ms, ms->sc_splited_line[i]) == ERROR)
						break ;
					if (ms->pl_splited_count == 0)
					{
						ms->redirect_flag = false;
						args = split_command(ms->sc_splited_line[i]);
						parse_args(ms, list, args);
						if ((status = execute(ms, list, args)) == ERROR)
						{
							free(args);
							break;
						}
					}
					else
					{
						j = 0;
						ms->start_pipe_process = false;
						while (j < ms->pl_splited_count)
						{
							ms->redirect_flag = false;
							args = split_command(ms->pl_splited_line[j++]);
							parse_args(ms, list, args);
							//ここで実行してfdを渡してく？
							if ((status = execute(ms, list, args)) == ERROR)
							{
								free(args);
								break;
							}
						}
						j = 0;
						while (j < ms->pl_splited_count)
							free(ms->pl_splited_line[j++]);
						free(ms->pl_splited_line);
					}
					free(args);
				}
				else
				{
					ms->redirect_flag = false;
					args = split_command(ms->sc_splited_line[i]);
					parse_args(ms, list, args);
					if ((status = execute(ms, list, args)) == ERROR)
						break; //freeが甘い
				}
				free(ms->sc_splited_line[i++]);
				free(args);
			}
			free(ms->sc_splited_line);
		}
		else
		{
			if (ms->pipeline_flag == true)
			{
				if (split_command_line_with_pipeline(ms, line) == ERROR)
					break ;
				if (ms->pl_splited_count == 0)
				{
					ms->redirect_flag = false;
					args = split_command(ms->sc_splited_line[i]);
					parse_args(ms, list, args);
					if ((status = execute(ms, list, args)) == ERROR)
					{
						free(args);
						break;
					}
				}
				else
				{
					j = 0;
					ms->start_pipe_process = false;
					while (j < ms->pl_splited_count)
					{
						ms->redirect_flag = false;
						args = split_command(ms->pl_splited_line[j++]);
						parse_args(ms, list, args);
						//ここで実行してfdを渡してく？
						if ((status = execute(ms, list, args)) == ERROR)
						{
							free(args);
							break;
						}
					}
					j = 0;
					while (j < ms->pl_splited_count)
						free(ms->pl_splited_line[j++]);
					free(ms->pl_splited_line);
				}
			}
			else
			{
				ms->redirect_flag = false;
				args = split_command(line);
				parse_args(ms, list, args);
				if ((status = execute(ms, list, args)) == ERROR)
					break; //freeが甘い
				free(args);
			}
		}
		free(line);
	}
}

void	signal_handler(int signum)
{
	if (fork_flag == false)
	{
		if (signum == SIGINT)
		{
			ft_putstr_fd("\b\b  \b\b", 1);
	 		ft_putstr_fd("\n\x1b[32mminishell: \x1b[m", 1);
		}
		else if (signum == SIGQUIT)
			ft_putstr_fd("\b\b  \b\b", 1);
	}
}

int 	main(int argc, char **argv)
{
	t_ms 		ms;
	str_list	list;

	(void)argc;
	(void)argv;
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, &signal_handler);
	minishell_loop(&ms, &list);
	return (0);
}

// void	minishell_loop(t_ms *ms, str_list *list)
// {
// 	char	*line;
// 	char	**args;
// 	int		i;
// 	int		status;

// 	status = 1;
// 	while (status)
// 	{
// 		ft_putstr_fd("\x1b[32mminishell: \x1b[m", 1);
// 		if (!(line = read_command_line(ms)))
// 			continue;
// 		if (split_command_line_with_semicolon(ms, line) == ERROR)
// 			continue;
// 		if (ms->semicolon_flag == true)
// 		{
// 			i = 0;
// 			while (i < ms->sc_splited_count)
// 			{
// 				ms->redirect_flag = false;
// 				args = split_command(ms->sc_splited_line[i]);
// 				parse_args(ms, list, args);
// 				status = execute(ms, list, args);
// 				free(ms->sc_splited_line[i++]);
// 				free(args);
// 			}
// 			free(ms->sc_splited_line);
// 		}
// 		else
// 		{
// 			ms->redirect_flag = false;
// 			//pipe判定
// 			//if(pipe == true)
// 			// {
// 			// 	while (//pipeの数+1)
// 			// 	{
// 			// 		args = split_command(line);
// 			// 		parse_args(ms, list, args);
// 			// 		g_status = execute(ms, list, args);
// 			// 		free(args);
// 			// 	}
// 			// }
// 			//else
// 			args = split_command(line);
// 			parse_args(ms, list, args);
// 			status = execute(ms, list, args);
// 			free(args);
// 		}
// 		free(line);
// 	}
// }
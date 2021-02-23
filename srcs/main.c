#include "../include/minishell.h"

char	*builtin_str[] =
{
	"echo",
	"pwd",
	"env",
	"exit",
	"cd",
	"export",
	"unset"
};

int		(*builtin_func[])(char **) = {
	&run_echo,
	&run_pwd,
	&run_env,
	&run_exit,
	&run_cd,
	&run_export,
	&run_unset
};

int		num_builtins() {
	return sizeof(builtin_str) / sizeof(char *);
}

int		launch(t_ms *ms, char **args)
{
	pid_t	pid;
	int		status;

	pid = fork();
	status = 0;
	if (pid == 0)
	{
		if (execvp(args[0], args) == ERROR)
			put_error();
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		put_error();
	else
	{
		while (WIFEXITED(status) && !WIFSIGNALED(status))
			ms->wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}

int		execute(t_ms *ms, char **args)
{
	int		i;

	if (args[0] == NULL)
		return (1);
	i = 0;
	while (i < num_builtins())
	{
		if (ft_strcmp(args[0], builtin_str[i]) == 0)
			return (*builtin_func[i])(args);
		i++;
	}
	return (launch(ms, args));
}

void	split_command_line(t_ms *ms, char *line)
{
	ms->semicolon_flg = false;
	if (ft_strchr(line, ';'))
	{
		ms->semicolon_flg = true;
		ms->splited_line_num = 0;
		if (!(ms->splited_line = ft_split(line, ';')))
			put_error_exit();
		while (ms->splited_line[ms->splited_line_num] != NULL)
			ms->splited_line_num++;
		free(line);
	}
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

	ms->loop_count = 0;
	if (!(line = ft_calloc(1, sizeof(char))))
		put_error_exit();
	if (!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		put_error_exit();
	while ((rt = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		ms->loop_count++;
		buffer[rt - 1] = '\0';
		if (!(line = ft_free_strjoin(line, buffer)))
		{
			free(buffer);
			put_error_exit();
		}
		if ((rt - 1) <= BUFFER_SIZE || ms->loop_count > 256)
			break;
	}
	if (ms->loop_count > 256)
	{
		ft_putendl_fd("minishell: Argument list too long", 2);
		free(buffer);
		free(line);
		exit(EXIT_FAILURE);
	}
	if (rt == ERROR)
	{
		free(buffer);
		free(line);
		put_error_exit();
	}
	if (*line == '\n')
	{
		*line = '\0';
		free(buffer);
		return (line);
	}
	free(buffer);
	return (line);
}

void	minishell_loop(t_ms *ms)
{
	char	*line;
	char	**args;
	int		status;
	int		count;

	status = 1;
	while (status)
	{
		ft_putstr_fd("\x1b[32mminishell: \x1b[m", 1);
		line = read_command_line(ms);
		split_command_line(ms, line);
		if (ms->semicolon_flg == true)
		{
			count = 0;
			while (count < ms->splited_line_num)
			{
				args = split_command(ms->splited_line[count]);
				status = execute(ms, args);
				free(ms->splited_line[count++]);
				free(args);
			}
			free(ms->splited_line);
		}
		else
		{
			args = split_command(line);
			status = execute(ms, args);
			count++;
			free(line);
			free(args);
		}
	}
}

int main(int argc, char **argv)
{
	t_ms ms;

	(void)argc;
	(void)argv;
	minishell_loop(&ms);
	// Perform any shutdown/cleanup.
	return (0);
}

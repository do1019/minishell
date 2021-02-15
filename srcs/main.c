/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 18:46:21 by dogata            #+#    #+#             */
/*   Updated: 2021/02/16 01:19:58 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*builtin_str[] = {
	"echo",
	"pwd",
	"env",
	"exit"
};

int		(*builtin_func[])(char **) = {
	&run_echo,
	&run_pwd,
	&run_env,
	&run_exit
};

int		num_builtins() {
	return sizeof(builtin_str) / sizeof(char *);
}

int		launch(char **args)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	pid = fork();
	status = 0;
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
			perror("lsh");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		perror("lsh");
	else
	{
		while (WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}

int		execute(char **args)
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
	return (launch(args));
}

char	**split_command_line(char *line)
{
	int		buffer_size;
	int		position;
	char	**tokens;
	char	*token;

	buffer_size = BUFFER_SIZE;
	position = 0;
	if (!(tokens = malloc(sizeof(char *) * buffer_size)))
	{
		printf("minishell: allocation error\n");
		exit(EXIT_FAILURE);
	}
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
			{
				printf("minishell: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOK_DELIM);
	}
	tokens[position] = NULL;
	return (tokens);
}

char	*read_command_line(void)
{
	char	*buffer;
	char	*line;
	//char	*tmp_line;
	int		errornum;
	int		rt;
	int		loop_count;

	loop_count = 0;
	if (!(line = malloc(sizeof(char) * 1)))
	{
		errornum = errno;
		write(2, "minishell: ", 12);
		write(2, strerror(errornum), ft_strlen(strerror(errornum)) + 1);
		write(2, "\n", 2);
		exit(EXIT_FAILURE);
	}
	if (!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
	{
		errornum = errno;
		write(2, "minishell: ", 12);
		write(2, strerror(errornum), ft_strlen(strerror(errornum)) + 1);
		write(2, "\n", 2);
		exit(EXIT_FAILURE);
	}
	*line = '\0';
	printf("test2\n"); //
	while ((rt = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		printf("test3\n");
		if (loop_count > 256)
			break;
		loop_count++;
		buffer[rt] = '\0';
		if (!(line = ft_free_strjoin(line, buffer)))
		{
			errornum = errno;
			write(2, "minishell: ", 12);
			write(2, strerror(errornum), ft_strlen(strerror(errornum)) + 1);
			write(2, "\n", 2);
			free(buffer);
			exit(EXIT_FAILURE);
		}
	}
	if (loop_count > 256)
	{
		write(2, "minishell: ", 12);
		write(2, "Argument list too long\n", 24);
		free(buffer);
		free(line);
		exit(EXIT_FAILURE);
	}
	if (rt == ERROR)
	{
		errornum = errno;
		write(2, "minishell: ", 12);
		write(2, strerror(errornum), ft_strlen(strerror(errornum)) + 1);
		write(2, "\n", 2);
		free(buffer);
		free(line);
		exit(EXIT_FAILURE);
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

void	minishell_loop(void)
{
	char	*line;
	char	**args;
	int		status;

	status = 1;
	while (status)
	{
		write(1, "minishell: ", 12);
		printf("test1"); //
		line = read_command_line();
		args = split_command_line(line);
		status = execute(args);
		free(line);
		free(args);
	}
}

int main(int argc, char **argv)
{
	// Load config files, if any.

	(void)argc;
	(void)argv;
	minishell_loop();
	// Perform any shutdown/cleanup.
	return (0);
}

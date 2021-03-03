#include "../include/minishell.h"

void	input_redirect(char *command, char **argv, char *filename, int redirect_flag)
{
	int			fd;

	if (redirect_flag == 1)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IREAD | S_IWRITE);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	close(1);
	if (dup2(fd, 1) < 0)
	{
		perror("dup2");
		close(fd);
		exit(1);
	}
	close(fd);
	execvp(command, argv);
}

void	output_redirect(char *command, char **argv, char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	close(0);
	if (dup2(fd, 0) < 0)
	{
		perror("dup2");
		close(fd);
		exit(1);
	}
	close(fd);
	execvp(command, argv);
}

int		run_redirect(str_list *list)
{
	str_list	*current_list;
	int			child;
	int			status;

	if ((child = fork()) < 0)
	{
		perror("fork");
		exit(1);
	}
	current_list = list;
	while (current_list->redirect_flag == 0)
		current_list = current_list->next;
	if (child == 0)
	{
		if (current_list->redirect_flag == 1 || current_list->redirect_flag == 2)
			input_redirect(current_list->argv[0], current_list->argv, current_list->nex_str, current_list->redirect_flag);
		else if (current_list->redirect_flag == 3)
			output_redirect(current_list->argv[0], current_list->argv, current_list->nex_str);
	}
	else
	{
		if (wait(&status) < 0)
		{
			perror("wait");
			exit(1);
		}
	}
	return (1);
}

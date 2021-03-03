#include "../include/minishell.h"

static int	is_valid_semicolon_syntax(char *line, int num)
{
	if (line[num])
		num += 1;
	while (line[num])
	{
		if (line[num] == ' ')
			num++;
		//暫定
		else if (line[num] == ';' || line[num] == '|')
		{
			ft_putstr_fd("\x1b[32mminishell: \x1b[msyntax error near unexpected token `", 2);
			ft_putchar_fd(line[num], 2);
			ft_putendl_fd("'", 2);
			return (ERROR);
		}
		else
			break ;
	}
	return (0);
}

static void	is_valid_semicolon_exists(t_ms *ms, char *line)
{
	int i;

	i = 0;
	ms->semicolon_num = 0;
	ms->skip_quate_flag = false;
	while (line[i])
	{
		is_skip_quates(ms, line, i);
		if (ms->skip_quate_flag == false && line[i] == ';')
		{
			ms->semicolon_num++;
			ms->semicolon_flag = true;
		}
		i++;
	}
	ms->loop_count = ms->semicolon_num + 1;
	ms->sc_splited_count = 0;
}

static int	create_splited_line(t_ms *ms, char *line, int *i, int *j)
{
	char *tmp;

	ms->sc_splited_count++;
	if (ms->sc_splited_count == 1)
		if (!(ms->sc_splited_line =
			ft_calloc(sizeof(char *), ms->semicolon_num + 1)))
			return (put_error_rt());
	if (!(tmp = ft_substr(line, *j, *i - *j)))
		return (put_error_rt());
	if (!(ms->sc_splited_line[ms->sc_splited_count - 1] = ft_strtrim(tmp, " ")))
		return (put_error_rt());
	*j = *i + 1;
	free(tmp);
	return (0);
}

static int	is_valid_syntax(t_ms *ms, char *line, int i)
{
	int k;

	if (is_valid_semicolon_syntax(line, i) == ERROR)
	{
		k = 0;
		while (k < ms->sc_splited_count)
			free(ms->sc_splited_line[k++]);
		free(line);
		return (ERROR);
	}
	return (0);
}

int			split_command_line_with_semicolon(t_ms *ms, char *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	ms->semicolon_flag = false;
	if (ft_strchr(line, ';'))
	{
		is_valid_semicolon_exists(ms, line);
		while (ms->loop_count)
		{
			is_skip_quates(ms, line, i);
			if (ms->skip_quate_flag == false &&
				(line[i] == ';' || line[i] == '\0'))
			{
				ms->loop_count--;
				if (is_valid_syntax(ms, line, i) == ERROR)
					return (ERROR);
				if (create_splited_line(ms, line, &i, &j) == ERROR)
					return (ERROR);
			}
			i++;
		}
	}
	return (0);
}

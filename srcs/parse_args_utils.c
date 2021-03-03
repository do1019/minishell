#include "../include/minishell.h"

void	is_skip_quates(t_ms *ms, char *line, int i)
{
	if ((line[i] == '\'' || line[i] == '\"') && ms->skip_quate_flag == false)
		ms->skip_quate_flag = true;
	else if ((line[i] == '\'' || line[i] == '\"')
											&& ms->skip_quate_flag == true)
		ms->skip_quate_flag = false;
}

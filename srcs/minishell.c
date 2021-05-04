/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:05:43 by dogata            #+#    #+#             */
/*   Updated: 2021/04/29 17:10:33 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	void	delete_env_var_old_pwd_value(void)
{
	execution_minishell_once("unset OLDPWD");
	execution_minishell_once("export OLDPWD");
}

static	void	increase_shell_level(t_ms *ms)
{
	char		*prev_shell_level;
	char		*current_shell_level;
	int			prev_shell_level_num;

	prev_shell_level = getenv("SHLVL");
	if (prev_shell_level == NULL)
		ms->current_shell_level = 1;
	else
	{
		prev_shell_level_num = ft_atoi(prev_shell_level);
		ms->current_shell_level = prev_shell_level_num + 1;
	}
	current_shell_level = ft_itoa(ms->current_shell_level);
	if (current_shell_level == NULL)
		put_error_exit(NULL);
	edit_environ(ms, "SHLVL", current_shell_level);
	free_od_array(&current_shell_level, 0);
}

void	minishell_pre_init(t_ms *ms)
{
	*ms = (t_ms){0};
	ms->current_dir_path = getcwd(NULL, 0);
	if (ms->current_dir_path == NULL)
		put_error_exit(NULL);
}

int	main(int argc, char **argv)
{
	t_ms		ms;
	t_args		list;

	(void)argc;
	(void)argv;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	minishell_pre_init(&ms);
	increase_shell_level(&ms);
	delete_env_var_old_pwd_value();
	minishell_loop(&ms, &list);
	return (0);
}

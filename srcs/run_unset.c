#include "../include/minishell.h"

static int	is_unset_target(t_export *export, char **args, int ac)
{
	int			args_var_len;
	char		**div;
	t_env_lst	*current_content;

	div = div_at_equal(args[ac]);
	args_var_len = ft_strlen(div[0]);
	current_content = export->env_lst->content;
	if (!ft_memcmp(div[0], current_content->var_name, args_var_len + 1))
	{
		free(div[0]);
		free(div[1]);
		free(div);
		return (1);
	}
	free(div[0]);
	free(div[1]);
	free(div);
	return (0);
}

int					run_unset(char **args)
{
	extern char	**environ;
	char		**env;
	char 		**tmp;
	int			i;
	int			j;
	int			k;
	t_export		export;

	env = environ;
	if (args[1] != NULL)
	{
		export.args_count = 0;
		create_env_var_list(&export, env);
		//配列をカウント
		while (args[export.args_count] != NULL)
			export.args_count++;
		//元の環境変数の数 + 1(NULL) 分をcalloc
		tmp = ft_calloc(export.env_count + 1, sizeof(char *));
		//ここで一致するものがあれば無視してtmpに移す
		i = 0;
		j = 0;
		k = 1;
		//構造体に入れてfreeする,mainからのに入れればfreeしなくてもいい？ or exit関数でfree
		export.env_lst_front = export.env_lst;
		export.duplicate_flg = false;
		while (i < export.env_count)
		{
			while (k < export.args_count)
			{
				if (is_unset_target(&export, args, k))
				{
					i++;
					export.duplicate_flg = true;
					break;
				}
				k++;
			}
			if (export.duplicate_flg == true)
				export.duplicate_flg = false;
			else
				tmp[j++] = env[i++];
			k = 1;
			export.env_lst = export.env_lst->next;
		}
		environ = tmp;
		ft_lstclear_ms(&(export.env_lst_front));
	}
	return (1);
}

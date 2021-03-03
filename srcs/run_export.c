#include "../include/minishell.h"

char		**div_at_equal(char *env)
{
	char	**div;
	char	*equal;

	if (!(div = ft_calloc(2, sizeof(char *))))
		put_error_exit();
	if (!(equal = ft_strchr(env, '=')))
		div[0] = ft_strdup(env);
	else
	{
		div[0] = ft_substr(env, 0, equal - env);
		div[1] = ft_substr(env, equal - env + 1, ft_strlen(equal) - 1);
	}
	if ((equal && (!div[0] || !div[1])) || (!equal && !div[0]))
		put_error_exit();
	return (div);
}

static int	is_env_var_name_duplicated(t_export *export, char **args, int ac, int ec)
{
	int	rt;
	int	args_var_len;
	char **div;
	t_env_lst	*current_content;

	rt = 1;
	div = div_at_equal(args[ac]);
	args_var_len = ft_strlen(div[0]);
	while(rt < ec + 1)
	{
		current_content = export->env_lst->content;
		if (!ft_memcmp(div[0], current_content->var_name, args_var_len + 1))
		{
			if (current_content->value && !div[1])
				return (-1);
			free(div[0]);
			free(div[1]);
			free(div);
			return(rt);
		}
		export->env_lst = export->env_lst->next;
		rt++;
	}
	free(div[0]);
	free(div[1]);
	free(div);
	return (0);
}

static int	is_valid_export_argument(t_export *export, char *arg)
{
	int i;
	i = 0;

	export->equal_flag = false;
	while (arg[i])
	{
		if (i == 0 && !ft_isalpha(arg[i]))
			return (ERROR);
		if (i > 0 && !ft_isalnum(arg[i]) && arg[i] != '=' && export->equal_flag == false)
			return (ERROR);
		if (arg[i] == '=')
			export->equal_flag = true;
		i++;
	}
	return (0);
}

int			run_export(char **args)
{
	extern char	**environ;
	char		**env;
	char 		**tmp;
	t_env_lst	*current_content;
	int			i;
	int			j;
	int			rt;
	t_export	export;

	env = environ;
	if (args[1] == NULL)
	{
		create_env_var_list(&export, env);
		ft_lstsort(&(export.env_lst), export.env_count);
		export.tmp_lst = export.env_lst;
		while (export.env_count--)
		{
			current_content = export.env_lst->content;
			if (!ft_memcmp(current_content->var_name, "_", 1))
			{
				export.env_lst = export.env_lst->next;
				continue;
			}
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(current_content->var_name, 1);
			if (current_content->value)
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(current_content->value, 1);
				ft_putendl_fd("\"", 1);
			}
			else
				ft_putendl_fd("", 1);
			export.env_lst = export.env_lst->next;
		}
		ft_lstclear_ms(&(export.tmp_lst));
	}
	if (args[1] != NULL)
	{
		export.args_count = 0;
		create_env_var_list(&export, env);
		//配列をカウント
		while (args[export.args_count] != NULL)
			export.args_count++;
		//配列の数  + 元の環境変数の数 + 1(NULL) 分をcalloc
		tmp = ft_calloc(export.args_count + export.env_count, sizeof(char *));
		i = -1;
		while (++i < export.env_count)
			tmp[i] = env[i];
		j = 1;
		//構造体に入れてfreeする,mainからのに入れればfreeしなくてもいい？ or exit関数でfree
		export.env_lst_front = export.env_lst;
		while (j < export.args_count)
		{
			//エラー処理 どこまでエラーにするのか？bash準拠？
			if (is_valid_export_argument(&export, args[j]) == ERROR)
			{
				ft_putstr_fd("\x1b[32mminishell: \x1b[mexport: `", 1);
				ft_putstr_fd(args[j], 1);
				ft_putendl_fd("': not a valid identifier", 1);
				j++;
				continue;
			}
			export.env_lst = export.env_lst_front;
			if ((rt = is_env_var_name_duplicated(&export, args, j, export.env_count)) > 0)
				tmp[rt - 1] = ft_strdup(args[j]);
			else if (rt == 0)
			{
				//一致するものがなければ
				tmp[i++] = ft_strdup(args[j]);
				add_env_var_list(&export, args, j);
			}
			j++;
		}
		environ = tmp;
		ft_lstclear_ms(&(export.env_lst_front));
	}
	return (1);
}

//構造体関連もう少し整理、メインから持ってきたい
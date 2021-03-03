#include "../include/minishell.h"

int		ft_strchar_num(char *environ, int c)
{
	int		i;

	i = 0;
	while (environ[i] != '\0')
	{
		if (environ[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	convert_env(str_list *list, char *environ, int env_strlen)
{
	int		convert_strlen;
	int		i;
	int		j;
	char	*ptr;

	convert_strlen = ft_strlen(list->new_str) + ft_strlen(environ) -
		((env_strlen + 1) * 2);
	if (!(ptr = (char *)malloc(sizeof(char) * (convert_strlen + 1))))
		return ;
	i = -1;
	while (list->new_str[++i] != '$')
		ptr[i] = list->new_str[i];
	j = -1;
	while (environ[env_strlen + ++j + 1] != '\0')
		ptr[i + j] = environ[env_strlen + j + 1];
	while (list->new_str[i + 1 + env_strlen] != '\0')
	{
		ptr[i + j] = list->new_str[i + 1 + env_strlen];
		i++;
	}
	ptr[i + j] = '\0';
	list->new_str = ptr;
}

void	check_env(str_list *list, int e_posi, int env_strlen)
{
	char			*ptr;
	int				i;
	extern	char	**environ;

	if (!(ptr = (char *)malloc(sizeof(char) * (env_strlen + 1))))
		return ;
	i = -1;
	while (++i < env_strlen)
		ptr[i] = list->new_str[e_posi + i];
	i = -1;
	while (environ[++i])
	{
		if ((ft_strncmp(ptr, environ[i], env_strlen)) == 0)
		{
			if (ft_strchar_num(environ[i], '=') == env_strlen)
				convert_env(list, environ[i], env_strlen);
		}
	}
	free(ptr);
}

void	prepare_check_env(str_list *list)
{
	int		i;
	int		j;

	i = -1;
	while (list->new_str[++i] != '\0')
	{
		if (list->new_str[i] == '$')
		{
			j = 1;
			list->env_flag++;
			while (list->new_str[i + j] != '$' && list->new_str[i + j] != '\0')
				j++;
			check_env(list, i + 1, j - 1);
		}
	}
}

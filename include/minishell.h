#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>

# include "../libft/libft.h"
# include "export.h"
# include "unset.h"

# define BUFFER_SIZE 1024
# define TOK_BUFFER_SIZE 64
//# define MAX_BUFFER_SIZE 262144
# define TOK_DELIM " \t\r\n\a"

# define ERROR -1

typedef struct		s_ms
{
	char			**splited_line;
	bool			semicolon_flg;
	int				splited_line_num;
	pid_t			wpid;
	int				loop_count;
}					t_ms;

int		run_echo(char **args);
int		run_pwd(char **args);
int		run_env(char **args);
int		run_exit(char **args);

int		run_cd(char **args);
int		run_export(char **args);
int		run_unset(char **args);

void	put_error_exit();
void	put_error();

t_env_lst	*ft_lstnew_ms(char *env, char *front, char *back);
void		swap(t_list ***current);
void		ft_bubble_sort(t_list **current);
void		ft_lstsort(t_list **env_lst, int lst_count);
void		ft_lstclear_ms(t_list **env_lst);
char		**div_at_equal(char *env);
void		create_env_var_list(t_export *export, char **env);
void		add_env_var_list(t_export *export, char **args, int count);

#endif

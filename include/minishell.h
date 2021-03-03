#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <signal.h>

# include "../libft/libft.h"
# include "export.h"

# define BUFFER_SIZE 1024
# define TOK_BUFFER_SIZE 64
//# define MAX_BUFFER_SIZE 262144
# define TOK_DELIM " \t\r\n\a"

# define ERROR -1
# define READ 0
# define WRITE 1

typedef struct			s_ms
{
	char				**sc_splited_line;
	char				**pl_splited_line;
	int					sc_splited_count;
	int					pl_splited_count;
	int					semicolon_num;
	int					pipeline_num;
	bool				semicolon_flag;
	bool				pipeline_flag;
	bool				skip_quate_flag;
	bool				redirect_flag;
	int					loop_count;
	pid_t				pid;
	pid_t				wpid;
	int					current_pipe_fd[2];
	int					prev_pipe_fd[2];
	bool				start_pipe_process;
}						t_ms;

typedef	struct			str_list
{
	int					element;
	int					quote_flag;
	int					quote_num;
	int					env_flag;
	int					redirect_flag;
	char				*old_str;
	char				*new_str;
	char				*pre_str;
	char				*nex_str;
	char				**argv;
	struct	str_list	*next;
}str_list;

int						run_echo(str_list *list);
int						run_pwd(void);
int						run_env(void);
int						run_exit(str_list *list);
int						run_redirect(str_list *list);

int						run_cd(char **args);
int						run_export(char **args);
int						run_unset(char **args);

void					put_error_exit();
void					put_error();
int						put_error_rt();
char					*put_error_free(char **ptr);

t_env_lst				*ft_lstnew_ms(char *env, char *front, char *back);
void					swap(t_list ***current);
void					ft_bubble_sort(t_list **current);
void					ft_lstsort(t_list **env_lst, int lst_count);
void					ft_lstclear_ms(t_list **env_lst);
char					**div_at_equal(char *env);
void					create_env_var_list(t_export *export, char **env);
void					add_env_var_list(t_export *export, char **args, int count);

void					parse_args(t_ms *ms, str_list *list, char **args);
void					prepare_check_env(str_list *list);
void					init_list(str_list *list, int num);
void					create_list(str_list *list, int argc);

int						split_command_line_with_semicolon(t_ms *ms, char *line);
int						split_command_line_with_pipeline(t_ms *ms, char *line);
void					is_skip_quates(t_ms *ms, char *line, int i);
int						is_valid_pipeline_with_correct_syntax(t_ms *ms, char *line);

#endif

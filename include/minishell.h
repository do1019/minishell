/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:41:18 by hikeda            #+#    #+#             */
/*   Updated: 2021/04/29 17:47:06 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <termios.h>
# include <termcap.h>

# include "../libft/libft.h"

# define BUFFER_SIZE 1024
# define MAX_LINE_SIZE 262144
# define SEPARATOR " \t\r\n\a"

# define ERROR -1
# define READ 0
# define WRITE 1

# define UP 4283163
# define DOWN 4348699
# define LEFT 4479771
# define RIGHT 4414235

# define SIGNAL_PIPELINE_FLAG 1
# define SIGNAL_FORK_FLAG 2
# define SIGNAL_RESET_LINE_FLAG 4
# define SIGNAL_NEWLINE_FLAG 8

# define ERROR_BUILTINS 2
# define COMMAND_CAN_NOT_EXECUTE 126
# define COMMAND_NOT_FOUND 127
# define SYNTAX_ERROR 258

volatile sig_atomic_t	g_signal_flags;

typedef struct s_args
{
	int				element;
	int				num;
	int				sq_flag;
	int				dq_flag;
	int				bs_flag;
	int				osp;
	int				nsp;
	int				env_flag;
	int				red_num;
	int				red_err;
	int				fd_in;
	int				fd_out;
	int				fd_err;
	int				argc;
	char			*old_str;
	char			*new_str;
	char			**argv;
	char			**red_argv;
	char			**filename;
	struct s_args	*next;
}				t_args;

typedef struct s_env_list
{
	char	*env_var;
	char	*var_name;
	char	*value;
}				t_env_list;

typedef struct s_ms
{
	int				current_shell_level;
	char			**new_environ;
	bool			edit_env_flag;
	bool			add_old_pwd_flag;
	char			*current_dir_path;
	char			*tmp_current_dir_path;
	char			*tmp_old_pwd_path;
	int				line_length;
	char			*buffer;
	char			*old_line;
	char			*line;
	char			*new_line;
	int				lp;
	int				nlp;
	int				fnc;
	int				fnp;
	int				read_rt;
	int				his;
	char			*history[1096];
	int				c;
	char			*rd_line;
	int				rd_i;
	int				rd_p;
	char			**sc_splited_line;
	char			**pl_splited_line;
	int				sc_splited_count;
	int				pl_splited_count;
	int				semicolon_num;
	int				pipeline_num;
	bool			semicolon_flag;
	bool			pipeline_flag;
	bool			redirect_flag;
	int				redirect_num;
	int				main_loop_count;
	int				loop_count;
	char			**args;
	int				array_count;
	int				start;
	bool			separate_flag;
	bool			single_quate_flag;
	bool			double_quate_flag;
	bool			back_slash_flag;
	char			**new_args;
	char			**paths;
	pid_t			pid;
	pid_t			wpid;
	int				current_pipe_fd[2];
	int				prev_pipe_fd[2];
	bool			builtin_command_flag;
	int				exec_count;
	int				minishell_status;
	int				wpid_status;
	char			*getcwd_buf;
	char			**div;
	bool			empty_value;
	t_list			*env_lst;
	t_list			*tmp_lst;
	t_list			*env_lst_front;
	t_env_list		*current_content;
	char			**tmp_env;
	int				env_var_count;
	int				export_unset_args_count;
	bool			duplicate_flag;
	bool			equal_flag;
	t_args			*current_list;
	char			*converted_new_str;
	int				exit_code;
	char			*exe_file;
	char			*exe_file_path;
	bool			failure_found_env_path_flag;
	bool			has_slash_flag;
	struct termios	oldtio;
}				t_ms;

void			minishell_pre_init(t_ms *ms);

void			minishell_loop(t_ms *ms, t_args *list);
void			minishell_init(t_ms *ms);
void			execution_minishell_process(t_ms *ms, t_args *list);
void			free_lines(t_ms *ms);

char			*read_command_loop(t_ms *ms);
void			push_arrowkey(t_ms *ms);
void			push_anotherkey(t_ms *ms, int i, int j, int flag);
void			push_enter(t_ms *ms);
void			push_backspace(t_ms *ms, int i, int j);
void			ctrl_d(t_ms *ms);

void			split_command(t_ms *ms, char *line);

int				execute_command(t_ms *ms, t_args *list, char **args);
void			is_builtin_command(t_ms *ms, t_args *list);
void			check_builtin_and_redirect_command(t_ms *ms, t_args *list);
void			execute_buildin_command(t_ms *ms, t_args *list, char **args);

int				launch_command(t_ms *ms, t_args *list, char **args);
void			create_new_args_array_for_execve(t_ms *ms, \
													t_args *list, char **args);
void			close_and_dup_write(t_ms *ms);
void			close_and_dup_read(t_ms *ms);

int				count_colon(char *env_path);
char			*convert_new_str_for_create_exe_file_path(t_ms *ms, \
																char *new_str);
char			*find_executable_file_location(t_ms *ms);
char			*find_file_path(t_ms *ms, t_args *list);
void			create_exe_file_path(t_ms *ms, char **exe_file, \
												char **exe_file_path, int *i);
void			close_prev_pipe_fd(t_ms *ms);
void			put_error_exit_for_execve(char *s);

void			signal_handler(int signal_number);
void			signal_handler_in_launch(t_ms *ms);

int				run_echo(t_args *list);
int				run_pwd(t_ms *ms, t_args *list);
int				run_env(t_args *list);
int				run_exit(t_ms *ms, t_args *list);
int				run_redirect(t_ms *ms, t_args *list);
int				run_redirect_builtin_command(t_ms *ms, t_args *list);
void			convert_command_name(t_ms *ms, t_args *list);
int				check_redirect_command(char *str, int i);
void			check_filename(t_ms *ms, t_args *line);
void			check_filename_env(t_ms *ms, t_args *list);
int				ft_strchar_num(char *environ, int c);
void			check_consecutive_redirect(t_ms *ms, t_args *list);
void			reset_fd(t_args *list);
void			input_redirect(t_args *list, char *filename, int flag);
void			input_redirect_error(t_args *list, char *filename, int flag);
void			output_redirect(t_args *list, char *filename);

int				run_cd(t_ms *ms, t_args *list, char **args);
void			put_error_cd(t_args *list);
void			put_error_cd_2(t_args *list);
void			set_old_pwd_path(t_ms *ms);
void			add_old_pwd_key(char *old_pwd_value);
void			after_once_additional_old_pwd_path(t_ms *ms, char *rt);

int				run_export(t_ms *ms, t_args *list, char **args);
void			duplicate_env_to_tmp_env(t_ms *ms, char **env, int *count);
int				is_valid_export_argument(t_ms *ms, char *arg);
void			put_error_export_for_argument_exists(t_ms *ms);
void			check_duplicate_and_add_env_var(t_ms *ms, int *count);
int				is_env_var_name_duplicated(t_ms *ms, char *arg, \
															int env_var_num);
char			*convert_new_str_for_escape_sequence(char *new_str);
char			*convert_new_str(char *new_str);
void			free_environ_with_allocated_memory(t_ms *ms, char **environ);

int				run_unset(t_ms *ms, t_args *list, char **args);

void			prepare_export_unset_for_argument_exists(t_ms *ms, \
																t_args *list);
void			put_error_export_unset_for_argument_exists(t_ms *ms, char *s);
void			count_args_and_allocate_tmp_env_memory(t_ms *ms, t_args *list);
int				is_valid_unset_argument(t_ms *ms, t_args *list);

void			put_error_exit(char *s);
int				put_error_rt(t_ms *ms, int rt);
void			put_syntax_error_redirect(t_ms *ms);
void			put_syntax_error(t_ms *ms, char *s);
void			put_ambiguous_error(t_ms *ms, char *s);
void			put_filename_error(char *s);
void			put_command_error(char *s);

t_env_list		*ft_lstnew_ms(char *env, char *front, char *back);
void			ft_lstsort(t_list **env_lst, int lst_count);
void			ft_lstclear_ms(t_list **env_lst);
void			div_at_equal(t_ms *ms, char *env);
void			create_env_var_list(t_ms *ms, char **env);
void			add_env_var_list(t_ms *ms, char *arg);

void			parse_args(t_ms *ms, t_args *list, char **args);
void			check_redirect(t_ms *ms, t_args *list);
void			check_upcase(char *str, int i);
void			check_backslash(t_args *list);
int				check_dq_backslash(t_args *list);
void			check_env1(t_ms *ms);
void			convert_env(t_ms *ms, char *environ, \
												int e_posi, int env_strlen);
void			check_non_env(t_ms *ms, int e_posi);
void			init_list(t_args *list, int num);
void			create_list(t_args *list, int argc);
void			duplicate_list(t_args *list, int num);
void			free_args_list(t_args *list);
void			free_redirect_argv(t_args *list);
void			free_redirect_builtin_argv(t_args *list);
void			free_exit(t_ms *ms, t_args *list);
void			create_argv1(t_ms *ms, t_args *list);
void			change_argv(t_args *list, int i, int j, int k);
void			change_list(t_args *list, t_args *ptr, int i);

int				split_command_line_with_semicolon(t_ms *ms);
int				create_splited_line_with_semicolon(t_ms *ms, int *i, int *j);
int				split_command_line_with_pipeline(t_ms *ms, char *line);
int				is_head_charactor_exists(t_ms *ms, char c);
int				is_foot_charactor_exists(t_ms *ms, char c);
void			prepare_split_command(t_ms *ms);
void			is_valid_quates(t_ms *ms, char *line, int i);
bool			is_valid_next_quotes_exists(t_ms *ms, \
													char *line, int i, char c);
void			is_valid_backslash(t_ms *ms, char *line, int i);
int				is_valid_pipeline_with_correct_syntax(t_ms *ms);
int				check_pipeline_syntax(t_ms *ms);

void			edit_environ(t_ms *ms, char *target_key, char *new_value);
char			*ft_strjoin_clip_equal(char *s1, char *s2);

bool			is_space(char c);
int				count_array(char **array);
void			execution_minishell_once(char *read_command);

int				free_td_array(char ***array, int rt);
int				free_od_array(char **array, int rt);

#endif

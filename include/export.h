#ifndef EXPORT_H
# define EXPORT_H

typedef struct		s_export
{
	t_list			*env_lst;
	t_list			*tmp_lst;
	t_list			*env_lst_front;
	int				env_count;
	int				args_count;
	bool			duplicate_flg;
	bool			equal_flg;
}					t_export;

typedef struct		s_env_lst
{
	char			*env_var;
	char			*var_name;
	char			*value;
}					t_env_lst;

#endif
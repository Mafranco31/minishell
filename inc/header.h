/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:03:12 by mafranco          #+#    #+#             */
/*   Updated: 2024/04/03 16:29:59 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include <ctype.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <ncurses.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

int	g_error;

typedef struct s_qte
{
	char	*arg;
	char	*new;
	int		flag_err;
	int		qte_in;
	int		startwq;
	int		startrq;
	int		s;
	int		nba;
}		t_qte;

typedef struct s_cmd
{
	struct s_cmd	*next;
	char			*exe;
	char			**arg;
	int				nb_arg;
	int				pipe;
	int				inferior;
	int				inferior_two;
	int				superior;
	int				superior_two;
	char			*infile_name;
	char			*outfile_name;
	int				in;
	int				out;
	int				builtin;
}		t_cmd;

typedef struct s_utils
{
	int	i;
	int	j;
	int	n;
}		t_utils;

typedef struct s_data
{
	t_cmd	*cmd;
	t_cmd	*first;
	char	**env;
	char	*path;
	char	*input;
	int		nb_f;
	int		tmp_stdin;
	int		tmp_stdout;
	int		nb_pipes;
	int		**pipe;
	int		flag_err;
	int		err_msg;
	pid_t	pid;
	int		*real_time_pipe;
	int		f_err;
	int		f_signal;
}		t_data;

void	show_values(t_data *d);

/*	error_manager.c		*/

int		error_msg(char *str, int nb);

void	v_err_msg(char *str, int nb);

char	*c_err_msg(char *str, int nb);

/*	free_data.c		*/

void	free_commands(t_data *d, char *input);

void	free_data(t_data *d);

int		free_newcmd_parsing(t_data *d, t_cmd *cmd);

int		free_cmd_parsing(t_data *d, t_cmd *cmd);

/*	ft_getenv.c		*/

int		ft_getenv(t_data *d, char **envp);

/*	check_pipe.c			*/

int		check_pipe(char *input, int i, int c, int k);

/*	check_redir.c		*/

int		check_redir(char *input);

/*	check_quotes.c		*/

int		ft_go_next_quote(char *input, int i, char quote);

int		check_quotes(char *input);

void	which_quote2(t_qte *q, char *arg, int *i, t_data *d);

/*	ft_parse_input.c	*/

int		get_cmd(char *input, t_data *d, int *i);

int		ft_parse_input(char *input, t_data *d);

/*	utils_parse.c		*/

void	free_arg(char **arg, int k);

t_cmd	*ft_new_cmd(void);

int		is_dollar(char *input, int i);

void	get_redirection(char *input, int *i, t_data *d);

void	get_nb_arg(char *input, int i, t_data *d);

/*	utils.c			*/

int		ft_go_end_dollar(char *input, int i);

int		ft_is_blank(char *input);

int		ft_go_next_space(char *input, int i);

int		ft_nxt_qte(char *input, int i, char quote);

int		ft_skip_space(char *input, int i);

/*	ft_no_pipe.c		*/

int		ft_no_pipe_superior_two(t_data *d);

int		ft_no_pipe_superior(t_data *d);

void	ft_no_pipe_inferior_two(t_cmd *a);

int		ft_no_pipe_inferior(t_data *d);

void	ft_no_pipe(t_data *d);

void	ft_exec_pipe(t_data *d, int i, int j);

/*	ft_with_pipe.c		*/

void	ft_process(t_data *d, int i);

void	fd_problem(int nb, int close, int code, t_data *d);

void	ft_first_process(t_data *d);

void	ft_child(t_data *d, int i);

void	ft_last_process(t_data *d);

void	ft_close_pipes(t_data *d, int pipe_idx);

/*	utils_execution.c	*/

int		ft_nb_pipes(t_data *d);

int		ft_redirection(t_data *d, int x, int y, int z);

int		ft_infile(t_data *d, t_cmd *a, int x);

t_cmd	*ft_reorganize_cmd(t_cmd *cmd1, t_cmd *cmd2);

/*	check_access.c		*/

void	ft_permissions(int nb, char *file, int close, int a);

/*	ft_find_funcion.c	*/

void	ft_exec_funcion(t_data *d);

/*	all built in		*/

void	ft_cd(t_data *d, int i, char *path);
void	ft_echo(t_data *d);
void	ft_env(t_data *d);
char	*ft_dollar_sign(char *arg, int i, int start, t_data *d);
void	ft_exit(t_data *d, int i);
void	ft_export(t_data *d, int i, int j);
void	ft_pwd(t_data *d);
void	ft_unset(t_data *d, int i, int j, int len);

/*	ft_env.c		*/

void	ft_env_export(t_data *d);

/*	ft_unset.c		*/

int		free_env2(char **env, int j, int nb, int i);

/*	ft_execve.c		*/

void	ft_execve(t_data *d, char *path);

/*	ft_signal.c		*/

void	wait_signal(int i);

/*	parse_quotes.c		*/

void	parse_quotes(t_data *d, int j);

char	*add_in_front(t_qte *qte, int start, int len);

char	*add_in_front2(char *arg, t_qte *qte, int start, int len);

char	*replace_quote(t_qte *q, int *i, t_data *d);

/*	ft_dollar_in_quotes.c	*/

void	return_error_quotes(char *new, int nb);

int		find_next_space(char *arg, int i);

char	*insert_dlr(char *new, char *dlr, t_data *d);

char	*isrt_dlr_in_arg(t_qte *q, int i, t_data *d, char *dlr);

/*	ft_substr_minishell.c	*/

void	gt_dollar(char *dlr, t_data *d, t_qte *qte, int *i);

char	*del_simple_quotes(t_qte *qte, int *i, int start_a, t_data *d);

char	*ft_substr_mnsh(char const *s, unsigned int t, size_t len, t_data *d);

/*	ft_cd.c			*/

char	*ft_path(t_data *d, int i, int j);

/*	utils_substr.c		*/

void	free_qte(t_qte *qte, t_data *d, char *str);

void	del_arg_empty(t_data *d, int *k, char **ret);

void	is_dlr_sub(t_qte *qte, int *start, int *i, t_data *d);

void	is_qte_sub(t_qte *qte, int *start, int *i, t_data *d);

void	change_dlr_sub(t_qte *qte, int *start, int *i, t_data *d);

/*	dlr_err.c		*/

void	cge_dlr_rtrn(t_qte *qte);

void	dlr_interrogation(t_data *d, t_qte *qte, int *i);

void	get_redir_pipe(int *i, t_data *d);

/*	utils_cd.c		*/

char	*free_all_cd_arg(char **arg, int j);

char	*cd_double_point(char *path, char **arg, int j);

int		cd_set_pwd(t_data *d, int i);

int		cd_set_oldpwd(t_data *d, int pwd, int i);

/*	ft_check_path.c*/

char	*is_direct(char *path);

char	*ft_check_path(char *path, t_cmd *cmd, t_data *d, int i);

/*	ft_with_pipe2.c		*/

void	with_p1(t_data *d, int pipe_idx);

void	with_p2(t_data *d, int pipe_idx);

/*	ft_no_pipe2.c		*/

void	ft_np_inf2_2(t_data *d, int *p, char *line, char *tmp1);

void	free_char(char *to_free, char *to_free2, char *str, int nb);

/*	ft_export.c			*/

int		ft_valid_identifier(char **name, int i, int err, int c);

/*	utils_export.c		*/

int		prt_err(char *str, int err);

void	err_less(void);

int		ut_export(t_data *d, int i);

int		ex_insert_last(t_data *d, char **new, int len, int i);

/*	utils_export2.c		*/

int		ex_add_end(t_data *d, int i, int j, int k);

char	*ft_concat(char *name, char *value);

/*	utils_cd2.c		*/

void	err_chdir(t_data *d);

char	*cd_before(char *path);

/*	manage_inf2.c		*/

int		parse_inf2(t_data *d, int *i, char *input);

/*nuevos*/

void	ft_execve2(t_data *d, char *path);

void	ft_exec_funcion2(t_data *d);

void	ft_find_funcion2(t_data *d, char *cmd);

/*	ft_check_path_ex.c	*/

char	*ft_check_path_ex(char *path, t_cmd *cmd, t_data *d, int i);

/*	utils_execve.c		*/

int		execve_err_nb(int status);

/*	utils_env.c			*/

int		ft_alph_order(t_data *d, int i, int j);

void	ft_env_export2(char *env, int j);

void	retexport(t_data *d);

/*	ft_pre_reorganize.c	*/

void	ft_pre_reorganize(t_data *d);

#endif

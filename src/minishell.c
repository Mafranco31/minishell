/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:30:02 by mafranco          #+#    #+#             */
/*   Updated: 2024/04/03 16:29:16 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

/*void	show_values(t_data *d)
{
	printf("All went well, the input is good\n");
	int	i;
	int	nb = 1;
	t_cmd	*first;

	first = d->cmd;
	while (d->cmd)
	{
		i = 0;
		printf("\n\nfuncion number: %d\n", nb);
		printf("funcion:$>%s<$\n", d->cmd->exe);
		while (d->cmd->arg[i])
		{
			printf("arg %d: $>%s<$\n", i + 1, d->cmd->arg[i]);
			i++;
		}
		printf("| : %d, < : %d, << : %d, > : %d, >> : %d\n",
			d->cmd->pipe, d->cmd->inferior, d->cmd->inferior_two,
			d->cmd->superior, d->cmd->superior_two);
		printf("outfile: %s\n", d->cmd->outfile_name);
		printf("infile: %s\n", d->cmd->infile_name);
		printf("nb_arg: %i\n", d->cmd->nb_arg);
		d->cmd = d->cmd->next;
		nb++;
	}
	d->cmd = first;
	printf("\n");
}*/

/*void	ft_pre_reorganize(t_data *d)
{
	int	j;
	int	i;

	j = 1;
	i = 0;
	if (d->cmd->next && d->cmd->next->arg[1])
	{
		d->cmd->exe = d->cmd->next->arg[1];
		j = 1;
		while (d->cmd->next->arg[j])
			j++;
		d->cmd->arg = malloc(sizeof(char *) * (j + 1));
		while (d->cmd->next->arg[i + 1])
		{
			d->cmd->arg[i] = d->cmd->next->arg[i + 1];
			d->cmd->next->arg[i + 1] = NULL;
			i++;
		}
		d->cmd->arg[i] = NULL;
		d->cmd->nb_arg = d->cmd->next->nb_arg - 1;
		d->cmd->next->nb_arg = 1;
	}
}*/

void	ft_builtin(t_data *d, t_cmd *a)
{
	(void)d;
	while (a)
	{
		if (a->exe)
		{
			if ((ft_strncmp(a->exe, "echo", 4) == 0 && ft_strlen(a->exe) == 4)
				|| (ft_strncmp(a->exe, "cd", 2) == 0
					&& ft_strlen(a->exe) == 2)
				|| (ft_strncmp(a->exe, "pwd", 3) == 0
					&& ft_strlen(a->exe) == 3)
				|| (ft_strncmp(a->exe, "export", 6) == 0
					&& ft_strlen(a->exe) == 6)
				|| (ft_strncmp(a->exe, "unset", 5) == 0
					&& ft_strlen(a->exe) == 5)
				|| (ft_strncmp(a->exe, "env", 3) == 0
					&& ft_strlen(a->exe) == 3)
				|| (ft_strncmp(a->exe, "exit", 4) == 0
					&& ft_strlen(a->exe) == 4))
				a->builtin = 1;
			else
				a->builtin = 0;
		}
		a = a->next;
	}
}

void	exec_function2(t_data *d)
{
	t_cmd	*a;

	a = d->cmd;
	ft_builtin(d, a);
	if (d->nb_pipes > 0)
		ft_exec_pipe(d, 0, 0);
	else
		ft_no_pipe(d);
	if (dup2(d->tmp_stdin, 0) == -1)
		v_err_msg("error duplicating file descriptor\n", 103);
	if (dup2(d->tmp_stdout, 1) == -1)
		v_err_msg("error duplicating file descriptor\n", 104);
}

void	exec_funcion(t_data *d)
{
	d->tmp_stdin = dup(0);
	if (d->tmp_stdin == -1)
		v_err_msg("error duplicating file descriptor\n", 101);
	d->tmp_stdout = dup(1);
	if (d->tmp_stdout == -1)
		v_err_msg("error duplicating file descriptor\n", 102);
	d->cmd->outfile_name = NULL;
	d->cmd->infile_name = NULL;
	d->f_err = 0;
	if (d->cmd->exe == NULL)
		ft_pre_reorganize(d);
	if (ft_redirection(d, 0, 0, 0) == 1)
		return ;
	if (!d->cmd->exe)
		return ;
	d->first = d->cmd;
	d->nb_pipes = ft_nb_pipes(d);
	exec_function2(d);
}

void	start_shell(t_data *d)
{
	while (1)
	{
		wait_signal(1);
		d->input = readline("minishell:-->");
		d->f_signal = 0;
		if (!d->input)
			return ;
		if (d->input[0])
		{
			add_history(d->input);
			if (!ft_is_blank(d->input) && ft_parse_input(d->input, d) == 0)
			{
				d->f_err = 0;
				exec_funcion(d);
				free_commands(d, d->input);
			}
		}
		else
			free(d->input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*d;

	g_error = 0;
	if (argc != 1)
		return (error_msg("minishell.c does not need any arguments\n", 1));
	(void)argv;
	d = ft_calloc(sizeof(t_data), 1);
	if (!d)
		return (error_msg("error while allocating memory for data\n", 2));
	if (ft_getenv(d, envp) == 1)
		return (1);
	wait_signal(1);
	start_shell(d);
	free_data(d);
	return (0);
}

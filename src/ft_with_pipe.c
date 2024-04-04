/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_with_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:58:12 by dlitran           #+#    #+#             */
/*   Updated: 2024/04/03 16:13:09 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	fd_problem(int nb, int close, int code, t_data *d)
{
	if (d->f_err == 0)
	{
		g_error = nb;
		if (code == 1)
			ft_putstr_fd("close error\n", 2);
		if (code == 2)
			ft_putstr_fd("dup error\n", 2);
	}
	if (close == 1)
		exit(0);
}

void	ft_close_pipes(t_data *d, int pipe_idx)
{
	if (pipe_idx == d->nb_pipes)
		pipe_idx--;
	while (pipe_idx >= 0)
	{
		close(d->pipe[pipe_idx][0]);
		close(d->pipe[pipe_idx][1]);
		pipe_idx--;
	}
}

void	ft_process(t_data *d, int i)
{
	int	pipe_idx;

	pipe_idx = i;
	while (i > 0)
	{
		d->cmd = d->cmd->next;
		i--;
	}
	if (!d->cmd->exe)
		exit (g_error);
	with_p1(d, pipe_idx);
	with_p2(d, pipe_idx);
	ft_close_pipes(d, pipe_idx);
	ft_exec_funcion2(d);
}

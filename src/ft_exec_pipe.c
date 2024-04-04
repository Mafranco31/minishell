/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:30:02 by mafranco          #+#    #+#             */
/*   Updated: 2024/04/03 15:57:24 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	free_all_pipe(int **pipe, int i, int err, int nb)
{
	while (i > 0)
	{
		i--;
		free(pipe[i]);
	}
	free(pipe);
	if (err == 1)
	{
		perror("error allocating memory for pipes\n");
		g_error = nb;
	}
	if (err == 2)
	{
		perror("error fork\n");
		g_error = nb;
	}
}

void	ft_close_pipes2(t_data *d, int pipe_idx)
{
	close(d->pipe[pipe_idx - 2][0]);
	close(d->pipe[pipe_idx - 2][1]);
}

void	ft_call_process(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->nb_pipes + 1)
	{
		if (i < d->nb_pipes)
			pipe(d->pipe[i]);
		d->pid = fork ();
		if (d->pid == 0)
			ft_process(d, i);
		if (i >= 2)
			ft_close_pipes2(d, i);
		i++;
	}
}

void	ft_exec_pipe(t_data *d, int i, int j)
{
	j = d->nb_pipes + 1;
	d->pipe = malloc(sizeof(int *) * (d->nb_pipes + 1));
	if (!d->pipe)
		return (v_err_msg("error allocating memory for d->pipe\n", 29));
	while (i < d->nb_pipes)
	{
		d->pipe[i] = malloc(sizeof(int) * 2);
		if (!d->pipe[i])
			return (free_all_pipe(d->pipe, i, 1, 30));
		i++;
	}
	d->pipe[i] = NULL;
	ft_call_process(d);
	wait_signal(0);
	ft_close_pipes(d, j - 1);
	while (j > 0)
	{
		waitpid(-1, &g_error, 0);
		j--;
	}
	if (g_error == 256 || g_error == 512 || g_error == 32512)
		g_error = g_error / 256;
	free_all_pipe(d->pipe, i, 0, 0);
	return ;
}

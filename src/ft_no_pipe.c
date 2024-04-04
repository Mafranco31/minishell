/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:47:33 by dlitran           #+#    #+#             */
/*   Updated: 2024/04/03 16:09:10 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int	ft_no_pipe_superior_two(t_data *d)
{
	if (dup2(d->cmd->out, 1) == -1)
		fd_problem(84, 0, 2, d);
	return (0);
}

int	ft_no_pipe_superior(t_data *d)
{
	if (dup2(d->cmd->out, 1) == -1)
	{
		fd_problem(1, 0, 2, d);
		return (1);
	}
	close(d->cmd->out);
	return (0);
}

void	ft_no_pipe_inferior_two(t_cmd *a)
{
	char	*line;

	line = readline("> ");
	while (line && ft_strncmp(line, a->infile_name,
			ft_strlen(a->infile_name) + 1))
	{
		free(line);
		line = readline("> ");
	}
	free(line);
}

int	ft_no_pipe_inferior(t_data *d)
{
	if (dup2(d->cmd->in, 0) == -1)
	{
		fd_problem(86, 0, 2, d);
		return (1);
	}
	return (0);
}

void	ft_no_pipe(t_data *d)
{
	if (d->cmd->inferior > 0)
		if (ft_no_pipe_inferior(d))
			return ;
	if (d->cmd->superior > 0 || d->cmd->superior_two > 0)
		if (ft_no_pipe_superior(d))
			return ;
	ft_exec_funcion(d);
}

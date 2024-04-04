/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:43:29 by dlitran           #+#    #+#             */
/*   Updated: 2024/03/21 04:33:39 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int	ft_infile_two(t_cmd *a, int y)
{
	if (a->infile_name)
		free (a->infile_name);
	a->infile_name = ft_strdup(a->next->exe);
	ft_no_pipe_inferior_two(a);
	if (a->exe)
		a = ft_reorganize_cmd(a, a->next);
	y++;
	return (y);
}

int	ft_outfile(t_data *d, t_cmd *a, int z)
{
	if (a->outfile_name)
	{
		close (a->out);
		free (a->outfile_name);
	}
	a->outfile_name = ft_strdup(a->next->exe);
	a->out = open(a->outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (a->out == -1)
	{
		ft_permissions(1, a->outfile_name, 0, d->f_err);
		d->f_err = 1;
	}
	if (a->exe)
		a = ft_reorganize_cmd(a, a->next);
	z++;
	return (z);
}

int	ft_outfile_two(t_data *d, t_cmd *a, int l)
{
	if (a->outfile_name)
	{
		close (a->out);
		free (a->outfile_name);
	}
	a->outfile_name = ft_strdup(a->next->exe);
	a->out = open(a->outfile_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (a->out == -1)
	{
		ft_permissions(1, a->outfile_name, 0, d->f_err);
		d->f_err = 1;
	}
	if (a->exe)
		a = ft_reorganize_cmd(a, a->next);
	l++;
	return (l);
}

int	ft_redirection(t_data *d, int x, int y, int z)
{
	t_cmd	*a;
	int		l;

	l = 0;
	a = d->cmd;
	while (a)
	{
		if (a->inferior - x == 1)
			x = ft_infile(d, a, x);
		else if (a->inferior_two - y == 1)
			y = ft_infile_two(a, y);
		else if (a->superior - z == 1)
			z = ft_outfile(d, a, z);
		else if (a->superior_two - l == 1)
			l = ft_outfile_two(d, a, l);
		else
		{
			x = 0;
			y = 0;
			z = 0;
			l = 0;
			a = a->next;
		}
	}
	return (0);
}

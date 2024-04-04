/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:54:38 by dlitran           #+#    #+#             */
/*   Updated: 2024/03/20 20:39:31 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int	ft_nb_pipes(t_data *d)
{
	int		nb;
	t_cmd	*a;

	a = d->cmd;
	nb = 0;
	while (a)
	{
		if (a->pipe > 0)
			nb++;
		a = a->next;
	}
	return (nb);
}

static void	ft_recmd2(t_cmd *cmd1, t_cmd *cmd2, t_utils nb, char **new_args)
{
	free(cmd1->arg);
	cmd1->exe = new_args[0];
	nb.j = 1;
	free(cmd2->arg[0]);
	while (cmd2->arg[nb.j] && nb.i < cmd1->nb_arg)
	{
		new_args[nb.i] = strdup(cmd2->arg[nb.j]);
		if (!new_args[nb.i])
			return ;
		free(cmd2->arg[nb.j]);
		nb.i++;
		nb.j++;
	}
	new_args[nb.i] = NULL;
	cmd1->arg = new_args;
	free(cmd2->arg);
	cmd1->inferior += cmd2->inferior;
	cmd1->inferior_two += cmd2->inferior_two;
	cmd1->superior += cmd2->superior;
	cmd1->superior_two += cmd2->superior_two;
	cmd1->pipe = cmd2->pipe;
	cmd1->next = cmd2->next;
	free(cmd2);
}

t_cmd	*ft_reorganize_cmd(t_cmd *cmd1, t_cmd *cmd2)
{
	char	**new_args;
	t_utils	nb;

	nb.n = cmd1->nb_arg;
	cmd1->nb_arg = cmd1->nb_arg + cmd2->nb_arg - 1;
	new_args = malloc(sizeof(char *) * (cmd1->nb_arg + 1));
	if (!new_args)
		return (NULL);
	nb.i = 0;
	while (cmd1->arg[nb.i] && nb.i < nb.n)
	{
		new_args[nb.i] = strdup(cmd1->arg[nb.i]);
		if (!new_args[nb.i])
			return (NULL);
		free(cmd1->arg[nb.i]);
		nb.i++;
	}
	ft_recmd2(cmd1, cmd2, nb, new_args);
	return (cmd1);
}

int	ft_infile(t_data *d, t_cmd *a, int x)
{
	if (a->infile_name)
		free (a->infile_name);
	a->infile_name = ft_strdup(a->next->exe);
	a->in = open(a->infile_name, O_RDONLY, 0100);
	if (a->in == -1)
	{
		ft_permissions(1, a->infile_name, 0, d->f_err);
		d->f_err = 1;
	}
	if (a->exe)
		a = ft_reorganize_cmd(a, a->next);
	x++;
	return (x);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:02:50 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/16 22:00:17 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	free_commands(t_data *d, char *input)
{
	free(input);
	free_newcmd_parsing(d, d->first);
	d->nb_f = 0;
}

void	free_data(t_data *d)
{
	int	i;

	i = 0;
	while (d->env[i])
		i++;
	i--;
	while (i >= 0)
	{
		free(d->env[i]);
		i--;
	}
	free(d->env);
	free(d->path);
	free(d);
}

int	free_newcmd_parsing(t_data *d, t_cmd *cmd)
{
	int		i;
	t_cmd	*next;

	i = 0;
	while (i < d->nb_f && cmd)
	{
		next = cmd->next;
		if (d->flag_err != 2)
			free(cmd->exe);
		free_arg(cmd->arg, cmd->nb_arg);
		if (cmd->infile_name)
			free(cmd->infile_name);
		if (cmd->outfile_name)
			free(cmd->outfile_name);
		free(cmd);
		i++;
		cmd = next;
	}
	return (1);
}

int	free_cmd_parsing(t_data *d, t_cmd *cmd)
{
	int		i;
	t_cmd	*next;

	i = 0;
	while (i < d->nb_f - 1)
	{
		next = cmd->next;
		if (d->flag_err != 2)
			free(cmd->exe);
		free_arg(cmd->arg, cmd->nb_arg + 1);
		free(cmd);
		i++;
		cmd = next;
	}
	free(cmd);
	return (1);
}

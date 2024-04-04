/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:05:34 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/27 11:54:50 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

static int	is_flag_echo(char *arg)
{
	int	i;

	i = 1;
	if (arg && arg[0] == '-')
	{
		while (arg[i] && arg[i] == 'n')
			i++;
		if (!arg[i])
			return (1);
	}
	return (0);
}

static int	get_flag_echo(t_data *d)
{
	int	i;

	i = 1;
	while (d->cmd->arg[i] && is_flag_echo(d->cmd->arg[i]))
		i++;
	return (i);
}

void	ft_echo(t_data *d)
{
	int	i;
	int	flag;

	flag = get_flag_echo(d);
	i = flag;
	if (d->cmd->nb_arg > 1)
	{
		if (d->cmd->nb_arg > 1)
		{
			while (i < d->cmd->nb_arg - 1)
			{
				if (d->cmd->arg[i])
					printf("%s ", d->cmd->arg[i]);
				i++;
			}
			if (d->cmd->arg[i])
				printf("%s", d->cmd->arg[i]);
		}
	}
	if (flag == 1)
		printf("\n");
	g_error = 0;
}

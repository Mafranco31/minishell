/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 01:49:38 by mafranco          #+#    #+#             */
/*   Updated: 2024/04/03 16:04:02 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

static int	ft_is_numeric(char	*str)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	j = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9')
			&& str[i] != '+' && str[i] != '-' && (str[i] != 32
				|| !(str[i] < 8 || str[i] > 13)))
			return (0);
		if (str[i] == '+' || str[i] == '-')
			j += 1;
		if (str[i] > 47 && str[i] < 58)
			k += 1;
		if (j > 1)
			return (0);
		i++;
	}
	return (k);
}

static void	ext_if(t_data *d, int i)
{
	if (!ft_strncmp(d->cmd->arg[i], "--", 2)
		&& ft_strlen(d->cmd->arg[i]) == 2)
	{
		i++;
		if (!d->cmd->arg[i])
			exit(0);
	}
	if (!ft_is_numeric(d->cmd->arg[i]))
	{
		g_error = 255;
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(d->cmd->arg[i], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_commands(d, d->input);
		exit(g_error);
	}
	else
		g_error = ft_atoi(d->cmd->arg[i]);
}

void	ft_exit(t_data *d, int i)
{
	if (d->cmd->arg[i])
		ext_if(d, i);
	else if (d->cmd->nb_arg >= 2 && !d->cmd->arg[i])
	{
		g_error = 255;
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(d->cmd->arg[i], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_commands(d, d->input);
		exit(g_error);
	}
	else
		g_error = 0;
	if (d->cmd->nb_arg > 2 && ft_strncmp(d->cmd->arg[1], "--", 2)
		&& ft_strlen(d->cmd->arg[1]) == 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		g_error = 1;
	}
	free_commands(d, d->input);
	exit(g_error);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:51:06 by mafranco          #+#    #+#             */
/*   Updated: 2024/04/03 16:14:40 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int	ex_insert_plus(t_data *d, char **new, int len, int i)
{
	int		k;
	int		j;
	char	*name;
	char	*value;

	k = 0;
	while (d->cmd->arg[i][k] && d->cmd->arg[i][k] == '+')
		k++;
	name = ft_substr(d->cmd->arg[i], 0, k);
	j = k;
	while (d->cmd->arg[i][j])
		j++;
	value = ft_substr(d->cmd->arg[i], k, j);
	new[len] = ft_concat(name, value);
	if (!new[len])
		return (free_env2(new, len, 56, 1));
	new[len + 1] = NULL;
	free_env2(d->env, len, -1, 0);
	d->env = new;
	return (0);
}

int	ex_insert_last(t_data *d, char **new, int len, int i)
{
	int	k;

	k = 0;
	while (d->cmd->arg[i][k] && d->cmd->arg[i][k] == '=')
		k++;
	if (d->cmd->arg[i][k - 1] == '+')
		return (ex_insert_plus(d, new, len, i));
	new[len] = ft_strdup(d->cmd->arg[i]);
	if (!new[len])
		return (free_env2(new, len, 56, 1));
	new[len + 1] = NULL;
	free_env2(d->env, len, -1, 0);
	d->env = new;
	return (0);
}

int	ut_export(t_data *d, int i)
{
	if (d->cmd->arg[i][0] == '-')
	{
		err_less();
		return (1);
	}
	if (ft_valid_identifier(d->cmd->arg, 1, 1, 1))
		return (1);
	return (0);
}

void	err_less(void)
{
	ft_putstr_fd(" invalid option\n", 2);
	g_error = 2;
}

int	prt_err(char *str, int err)
{
	if (err == 1)
		ft_putstr_fd("export: '", 2);
	else
		ft_putstr_fd("unset: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_error = 1;
	return (1);
}

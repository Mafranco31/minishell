/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:08:07 by mafranco          #+#    #+#             */
/*   Updated: 2024/04/03 16:37:32 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int	find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i - 1] && str[i - 1] == '+')
			return (i - 1);
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	ex_replace(t_data *d, int i, int j)
{
	char	*new;
	int		k;

	k = 0;
	while (d->cmd->arg[i][k] != '=')
		k++;
	if (d->cmd->arg[i][k - 1] && d->cmd->arg[i][k - 1] == '+')
		return (ex_add_end(d, i, j, k));
	new = ft_strdup(d->cmd->arg[i]);
	if (!new)
		return (error_msg("error allocating memory for ft_export\n", 57));
	free(d->env[j]);
	d->env[j] = new;
	if (!ft_strncmp(new, "PATH=", 5))
	{
		free(d->path);
		d->path = ft_strdup(new);
	}
	return (0);
}

int	ex_insert(t_data *d, int i)
{
	int		len;
	char	**new;

	len = 0;
	while (d->env[len])
		len++;
	new = malloc(sizeof(char *) * (len + 2));
	if (!new)
		return (error_msg("error allocating memory for ft_export\n", 54));
	len = 0;
	while (d->env[len])
	{
		new[len] = ft_strdup(d->env[len]);
		if (!new[len])
			return (free_env2(new, len, 55, 1));
		len++;
	}
	return (ex_insert_last(d, new, len, i));
}

int	ft_valid_identifier(char **name, int i, int err, int c)
{
	int	j;

	while (name[i])
	{
		j = 0;
		if (!ft_isalpha(name[i][0]) && name[i][0] != '_')
			return (prt_err(name[i], err));
		while (name[i][j] && name[i][j] != '=')
		{
			if (!ft_isalnum(name[i][j]) && name[i][j] != '_'
				&& name[i][j] != '+')
				return (prt_err(name[i], err));
			if (!(name[i][j] > 47 && name[i][j] < 58))
				c = 0;
			if (name[i][j] == '+' && name[i][j + 1] != '=')
				return (prt_err(name[i], err));
			j++;
		}
		if (c == 1)
			return (prt_err(name[i], err));
		i++;
	}
	return (0);
}

void	ft_export(t_data *d, int i, int j)
{
	if (d->cmd->nb_arg == 1 || ut_export(d, i))
		return (retexport(d));
	while (d->cmd->arg[i])
	{
		if (find_equal(d->cmd->arg[i]) > 0)
		{
			j = 0;
			while (d->env[j] && ft_strncmp(d->cmd->arg[i], d->env[j],
					find_equal(d->cmd->arg[i])) != 0)
				j++;
			if (!d->env[j])
			{
				if (ex_insert(d, i) == 1)
					return ;
			}
			else
			{
				if (ex_replace(d, i, j) == 1)
					return ;
			}
		}
		i++;
	}
	g_error = 0;
}

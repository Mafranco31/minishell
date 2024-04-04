/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:09:32 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/25 15:39:55 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int	free_env2(char **env, int j, int nb, int i)
{
	while (j >= 0)
	{
		free(env[j]);
		j--;
	}
	free(env);
	if (nb >= 0)
		g_error = nb;
	if (i == 1)
		perror("error allocating memory for ft_export\n");
	else if (i == 2)
		perror("error allocating memory for ft_unset\n");
	return (1);
}

int	link_path(t_data *d, char **env)
{
	int		i;
	char	*new;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			new = ft_strdup(env[i]);
			if (!new)
				return (error_msg("error allocating memory for unset\n", 61));
			free(d->path);
			d->path = new;
			return (0);
		}
		i++;
	}
	free(d->path);
	d->path = ft_strdup("");
	if (!d->path)
		return (error_msg("error allocating memory for unset\n", 62));
	return (0);
}

int	unset_env(t_data *d, int j, int len, int k)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * len);
	if (!new)
		return (error_msg("error allocating memory for unset\n", 59));
	while (d->env[i])
	{
		if (i != j)
		{
			new[k] = ft_strdup(d->env[i]);
			if (!new[k])
				return (free_env2(new, k, 60, 2));
			k++;
		}
		i++;
	}
	new[k] = NULL;
	if (link_path(d, new) == 1)
		return (free_env2(new, k, -1, 2));
	free_env2(d->env, i, -1, 0);
	d->env = new;
	return (0);
}

void	ft_unset(t_data *d, int j, int i, int len)
{
	if (d->cmd->nb_arg == 1)
		return ;
	if (d->cmd->arg[i][0] == '-')
		return (err_less());
	if (ft_valid_identifier(d->cmd->arg, 1, 2, 1))
		return ;
	while (d->cmd->arg[i])
	{
		j = 0;
		while (d->env[j] && ft_strncmp(d->env[j], d->cmd->arg[i],
				ft_strlen(d->cmd->arg[i])) != 0)
		{
			j++;
		}
		if (d->env[j])
		{
			while (d->env[len])
				len++;
			if (unset_env(d, j, len, 0))
				return ;
		}
		i++;
	}
	g_error = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:33:28 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/27 16:05:47 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

static int	free_env(char **env, int i, int nb)
{
	i--;
	while (i >= 0)
	{
		free(env[i]);
		i--;
	}
	free(env);
	return (error_msg("error allocating memory for environment\n", nb));
}

static char	*next_chiffre(char *env, int i)
{
	int		nb;
	char	*tmp;

	tmp = ft_substr(env, 6, i - 6);
	if (!tmp)
		return (NULL);
	nb = ft_atoi(tmp);
	nb += 1;
	free(tmp);
	tmp = ft_itoa(nb);
	return (tmp);
}

static char	*new_shlvl(char *env)
{
	int		i;
	char	*ret;
	char	*tmp;

	ret = NULL;
	i = 6;
	if (env[6])
	{
		while (env[i] > 47 && env[i] < 58 && env[i])
			i++;
		tmp = next_chiffre(env, i);
		if (!tmp)
			return (NULL);
		ret = ft_strjoin("SHLVL=", tmp);
		free(tmp);
		if (!ret)
			return (NULL);
	}
	return (ret);
}

int	ft_getenv(t_data *d, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	d->env = ft_calloc(i + 1, sizeof(char *));
	if (d->env == NULL)
		return (error_msg("error allocating memory for environment\n", 3));
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
			d->env[i] = new_shlvl(envp[i]);
		else
		{
			d->env[i] = ft_strdup(envp[i]);
			if (ft_strncmp(envp[i], "PATH=", 5) == 0)
				d->path = ft_substr(d->env[i], 5, ft_strlen(d->env[i]));
		}
		if (d->env[i] == NULL)
			return (free_env(d->env, i, 4));
		i++;
	}
	d->env[i] = NULL;
	return (0);
}

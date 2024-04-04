/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:10:47 by mafranco          #+#    #+#             */
/*   Updated: 2024/04/03 15:59:43 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

/*static void	ft_env_export2(char *env, int j)
{
	printf("=");
	j += 1;
	printf("\"");
	while (env[j])
	{
		printf("%c", env[j]);
		j++;
	}
	printf("\"\n");
}

int	ft_alph_order(t_data *d, int i, int j)
{
	int	a;

	a = 0;
	while (d->env[i][a] && d->env[j][a])
	{
		if (d->env[i][a] > d->env[j][a])
			return (1);
		else if (d->env[i][a] < d->env[j][a])
			return (0);
		a++;
	}
	return (0);
}*/

int	ft_smaller(t_data *d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (d->env[j])
	{
		if (ft_alph_order(d, i, j))
			i = j;
		j++;
	}
	return (i);
}

int	ft_bigger(t_data *d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (d->env[j])
	{
		if (ft_alph_order(d, j, i))
			i = j;
		j++;
	}
	return (i);
}

int	ft_next_smaller(t_data *d, int last)
{
	int	i;
	int	j;

	if (last == ft_bigger(d))
		return (-1);
	i = ft_bigger(d);
	j = 0;
	while (d->env[j])
	{
		if (ft_alph_order(d, i, j) && ft_alph_order(d, j, last))
			i = j;
		j++;
	}
	return (i);
}

void	ft_env_export(t_data *d)
{
	int	i;
	int	j;

	i = ft_smaller(d);
	while (i != -1)
	{
		j = 0;
		printf("declare -x ");
		while (d->env[i][j] != '=')
		{
			printf("%c", d->env[i][j]);
			j++;
		}
		ft_env_export2(d->env[i], j);
		i = ft_next_smaller(d, i);
	}
	g_error = 0;
}

void	ft_env(t_data *d)
{
	int	i;

	i = 0;
	if (d->cmd->nb_arg == 1)
	{
		while (d->env[i])
		{
			printf("%s\n", d->env[i]);
			i++;
		}
		g_error = 0;
	}
	else
	{
		perror("env: too manny arguments\n");
		g_error = 52;
	}
}

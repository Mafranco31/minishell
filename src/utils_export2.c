/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:04:49 by mafranco          #+#    #+#             */
/*   Updated: 2024/04/03 16:14:58 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	retexport(t_data *d)
{
	if (d->cmd->nb_arg == 1)
		ft_env_export(d);
}

int	ex_add_end(t_data *d, int i, int j, int k)
{
	char	*value;
	char	*ret;

	value = ft_substr(d->cmd->arg[i], k + 1, ft_strlen(d->cmd->arg[i]));
	if (!value)
		return (error_msg("error substr\n", 115));
	ret = ft_strjoin(d->env[j], value);
	free(value);
	if (!ret)
		return (error_msg("error strjoin\n", 115));
	free(d->env[j]);
	d->env[j] = ret;
	return (0);
}

char	*ft_concat(char *name, char *value)
{
	char	*ret;

	if (!name || !value)
	{
		if (name)
			free(name);
		if (value)
			free(value);
		return (c_err_msg(" ft_substr error\n", 113));
	}
	ret = ft_strjoin(name, value);
	free(name);
	free(value);
	if (!ret)
		return (c_err_msg(" ft_strjoin error\n", 114));
	return (ret);
}

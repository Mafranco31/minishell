/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:07:22 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/13 01:24:00 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	ft_pwd(t_data *d)
{
	int	i;

	i = 0;
	while (d->env[i] && ft_strncmp(d->env[i], "PWD=", 4) != 0)
		i++;
	if (d->env[i])
	{
		printf("%s\n", (d->env[i] + 4));
		g_error = 0;
	}
}

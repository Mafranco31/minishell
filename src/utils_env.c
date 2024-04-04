/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:52:46 by mafranco          #+#    #+#             */
/*   Updated: 2024/04/03 16:14:20 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

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
}

void	ft_env_export2(char *env, int j)
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

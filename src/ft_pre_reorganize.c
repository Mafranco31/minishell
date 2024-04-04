/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pre_reorganize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:27:25 by mafranco          #+#    #+#             */
/*   Updated: 2024/04/03 16:29:07 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	ft_pre_reorganize(t_data *d)
{
	int	j;
	int	i;

	j = 1;
	i = 0;
	if (d->cmd->next && d->cmd->next->arg[1])
	{
		d->cmd->exe = d->cmd->next->arg[1];
		j = 1;
		while (d->cmd->next->arg[j])
			j++;
		d->cmd->arg = malloc(sizeof(char *) * (j + 1));
		while (d->cmd->next->arg[i + 1])
		{
			d->cmd->arg[i] = d->cmd->next->arg[i + 1];
			d->cmd->next->arg[i + 1] = NULL;
			i++;
		}
		d->cmd->arg[i] = NULL;
		d->cmd->nb_arg = d->cmd->next->nb_arg - 1;
		d->cmd->next->nb_arg = 1;
	}
}

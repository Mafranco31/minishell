/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlr_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:26:53 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/13 01:19:45 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	cge_dlr_rtrn(t_qte *qte)
{
	free(qte->new);
	qte->flag_err = 1;
	g_error = 26;
}

void	get_redir_pipe(int *i, t_data *d)
{
	*i += 1;
	d->cmd->pipe = 1;
}

void	dlr_interrogation(t_data *d, t_qte *qte, int *i)
{
	char	*err;

	(void)d;
	err = ft_itoa(g_error);
	if (!err)
	{
		qte->flag_err = 1;
		g_error = 27;
		return ;
	}
	qte->new = add_in_front2(err, qte, 0, ft_strlen(err));
	if (err)
		free(err);
	*i += 2;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:27:42 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/26 13:44:45 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	ft_permissions(int nb, char *file, int close, int a)
{
	(void)nb;
	if (a == 0)
	{
		ft_putstr_fd("error: ", 2);
		ft_putstr_fd(file, 2);
		if (errno == EACCES)
		{
			ft_putstr_fd(": Permission denied\n", 2);
			g_error = 126;
		}
		else if (errno == ENOENT)
		{
			ft_putstr_fd(": No such file or directory\n", 2);
			g_error = 1;
		}
		else
		{
			ft_putstr_fd(": error open\n", 2);
			g_error = 100;
		}
	}
	if (close == 1)
		exit(g_error);
}

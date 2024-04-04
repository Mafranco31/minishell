/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:35:00 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/17 17:23:46 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int	error_msg(char *str, int nb)
{
	ft_putstr_fd(str, 2);
	g_error = nb;
	return (1);
}

void	v_err_msg(char *str, int nb)
{
	ft_putstr_fd(str, 2);
	g_error = nb;
}

char	*c_err_msg(char *str, int nb)
{
	ft_putstr_fd(str, 2);
	g_error = nb;
	return (NULL);
}

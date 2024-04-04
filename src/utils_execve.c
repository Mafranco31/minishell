/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:36:47 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/21 12:41:06 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int	execve_err_nb(int status)
{
	if (status == 256)
		return (1);
	if (status == 512)
		return (2);
	if (status == 32512)
		return (127);
	return (status);
}

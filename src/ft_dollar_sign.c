/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_sign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:12:42 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/16 22:07:07 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	*return_error_dollar(char *new)
{
	if (new)
		free(new);
	perror("error allcoating memory for dollar insertion\n");
	return (NULL);
}

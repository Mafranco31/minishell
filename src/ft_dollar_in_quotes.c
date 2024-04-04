/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_in_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 00:25:07 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/16 22:07:02 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	return_error_quotes(char *new, int nb)
{
	if (new)
		free(new);
	perror("error allocating memory for quote parsing\n");
	g_error = nb;
}

int	find_next_space(char *input, int i)
{
	while (input[i] && (input[i] != ' ' && input[i] != '\t'
			&& input[i] != '\n' && input[i] != '\f'
			&& input[i] != '\r' && input[i] != '\v'
			&& input[i] != 34 && input[i] != 39
			&& input[i] != '$'))
		i++;
	return (i);
}

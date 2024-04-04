/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:45:07 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/21 10:09:28 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int	ft_go_end_dollar(char *input, int i)
{
	while (((input[i] >= 48 && input[i] <= 57) || (input[i] >= 65
				&& input[i] <= 90) || (input[i] >= 97
				&& input[i] <= 122)) && input[i])
		i++;
	return (i);
}

int	ft_go_next_space(char *input, int i)
{
	while (input[i] != ' ' && input[i] != '\t' && input[i] != '\n'
		&& input[i] != '\v' && input[i] != '\f' && input[i] != '\r'
		&& input[i])
	{
		if (input[i] == 92 && input[i + 1])
			i++;
		else if ((input[i] == 34 || input[i] == 39) && input[i + 1])
			i = ft_go_next_quote(input, i + 1, input[i]);
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			return (i);
		i++;
	}
	return (i);
}

int	ft_nxt_qte(char *input, int i, char quote)
{
	while (input[i])
	{
		if (input[i] == quote)
			return (i);
		i++;
	}
	return (i);
}

int	ft_skip_space(char *input, int i)
{
	while ((input[i] == ' ' || input[i] == '\t' || input[i] == '\n'
			|| input[i] == '\v' || input[i] == '\f' || input[i] == '\r'
			|| input[i] < 0) && input[i])
		i++;
	return (i);
}

int	ft_is_blank(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != '\t' && input[i] != '\n' && input[i] != '\v'
			&& input[i] != '\f' && input[i] != '\r'
			&& input[i] != ' ')
			return (0);
		i++;
	}
	free(input);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 00:29:45 by mafranco          #+#    #+#             */
/*   Updated: 2024/04/04 14:45:56 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

static int	prt_newline_err(void)
{
	g_error = 258;
	ft_putstr_fd(" syntax error near unexpected token \'newline\'\n", 2);
	return (1);
}

static int	prt_check_redir(char c)
{
	g_error = 258;
	ft_putstr_fd(" syntax error near unexpected token \'", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("\'\n", 2);
	return (1);
}

static int	no_end_redir(char *input, int i)
{
	while (input[i] && (input[i] == '<' || input[i] == '>'))
		i++;
	while (input[i] && input[i] == ' ')
		i++;
	if (!input[i])
		return (1);
	return (0);
}

int	dbl_inf(int c, char *input, int *i)
{
	if (c == 1)
		return (prt_check_redir(input[*i]));
	if (no_end_redir(input, *i))
		return (prt_newline_err());
	if (input[*i + 1] && input[*i + 1] == input[*i])
	{
		*i += 1;
		if (!input[*i + 1] || input[*i + 1] == '<' || input[*i + 1] == '>')
			return (prt_check_redir(input[*i]));
		if (input[*i] == '<' && input[*i + 1])
		{
			*i = ft_skip_space(input, *i);
			if (input[*i] == '!' && input[*i])
				return (error_msg("error : event not found\n", 0));
			while (ft_isprint(input[*i]) && input[*i] != ' ')
				*i += 1;
			return (2);
		}
	}
	return (0);
}

int	check_redir(char *input)
{
	int	i;
	int	c;
	int	er;

	i = 0;
	c = 0;
	er = 0;
	while (input[i])
	{
		if ((input[i] == 39 || input[i] == 34) && input[i + 1])
		{
			i = ft_go_next_quote(input, i + 1, input[i]);
			c = 0;
		}
		else if (input[i] == '<' || input[i] == '>')
		{
			er = dbl_inf(c, input, &i);
			if (er == 1)
				return (1);
			else if (er != 2)
				c = 1;
			else
				c = 0;
			i++;
		}
		else if (ft_isprint(input[i]) && input[i] != ' ')
		{
			c = 0;
			i++;
		}
		else
			i++;
	}
	return (0);
}

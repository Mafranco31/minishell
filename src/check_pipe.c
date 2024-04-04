/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:00:51 by mafranco          #+#    #+#             */
/*   Updated: 2024/04/04 14:36:51 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

static char	next_redir(char *input, int i)
{
	while (!ft_isprint(input[i]) || input[i] == ' ')
		i++;
	return (input[i]);
}

static int	after_pipe2(char *in, int *i, int j)
{
	if (in[j] == '|')
	{
		while ((in[*i + 1] == ' ' || in[*i + 1] == '<'
				|| in[*i + 1] == '>') && in[*i + 1])
			*i += 1;
		return (2);
	}
	else
	{
		if (in[j] == '>' && in[j + 1] == '>' && next_redir(in, j + 2) == '|')
			return (0);
		if (in[j] == '<' && in[j + 1] == '<' && next_redir(in, j + 2) == '|')
		{
			write(1, "ici\n", 4);
			return (0);
		}
		if (in[j] == '<' && next_redir(in, j + 1) == '|')
			return (0);
		while (in[*i + 1] && (in[*i + 1] == '<' || in[*i + 1] == '>'
				|| in[*i + 1] == '|'))
			*i += 1;
		return (2);
	}
}

static int	after_pipe(char *inpt, int *i, int c, int j)
{
	if (c == 2 && inpt[j] == '|')
		return (0);
	if (c == 0)
	{
		while ((inpt[*i + 1] == '|' || inpt[*i + 1] == '<'
				|| inpt[*i + 1] == '>' || inpt[*i + 1] == ' ') && inpt[*i + 1])
			*i += 1;
		if (inpt[j] == '>' && next_redir(inpt, j + 1) == '|')
			return (2);
		else if (inpt[j] == '<' && inpt[j + 1] == '<'
			&& next_redir(inpt, j + 2) == '|')
			return (0);
		else if (inpt[j] == '>' && inpt[j + 1] == '>'
			&& next_redir(inpt, j + 2) == '|')
			return (0);
		else if (inpt[j] == '<' && next_redir(inpt, j + 1) == '|')
			return (0);
		else if (inpt[j] == '|')
			return (0);
		else
			return (2);
	}
	else
		return (after_pipe2(inpt, i, *i));
}

static int	check_pipe2(char *input, int *i, int *c, int *k)
{
	*c = after_pipe(input, i, *c, *i);
	if (*c == 0)
		return (error_msg(" syntax error near unexpected token '|'\n", 2));
	if (input[*i] == '|')
		*k = 1;
	else
		*k = 0;
	return (0);
}

int	check_pipe(char *input, int i, int c, int k)
{
	while (input[i])
	{
		i = ft_skip_space(input, i);
		if ((input[i] == 39 || input[i] == 34) && input[i + 1])
		{
			i = ft_go_next_quote(input, i + 1, input[i]);
			c = 1;
		}
		else if (!(input[i] == '<' || input[i] == '>' || input[i] == '|'))
		{
			c = 1;
			i++;
		}
		else
		{
			if (check_pipe2(input, &i, &c, &k))
				return (1);
			i++;
		}
	}
	if ((c == 0 || c == 2) && k == 1)
		return (error_msg(" syntax error near unexpected token '|'\n", 2));
	return (0);
}

/*
int	check_pipe(char *input, int i, int c)
{
	while (input[i])
	{
		i = ft_skip_space(input, i);
		if ((input[i] == 39 || input[i] == 34) && input[i + 1])
		{
			i = ft_go_next_quote(input, i + 1, input[i]);
			c = 1;
		}
		else if (!(input[i] == '<' || input[i] == '>' || input[i] == '|'))
			c = 1;
		else if (input[i] == '|')
		{
			if (c == 0)
				return (error_msg(" syntax error near unexpected token '|'\n",
						2));
			c = 0;
		}
		else
			c = 0;
		i++;
	}
	if (c == 0)
		return (error_msg(" syntax error near unexpected token '|'\n", 2));
	return (0);
}*/

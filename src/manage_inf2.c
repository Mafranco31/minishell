/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_inf2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:58:18 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/21 03:53:00 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

static int	go_start_inf2(char *input, int i)
{
	while (input[i] && (input[i] == ' ' || input[i] == '\t' || input[i] == '\n'
			|| input[i] == '\v' || input[i] == '\f' || input[i] == '\r'))
		i++;
	return (i);
}

static void	add_pipe_inf2(t_data *d, int i, char *input)
{
	while (input[i] && (!ft_isprint(input[i]) && input[i] != ' '))
		i++;
	if (input[i])
		d->cmd->pipe = 1;
}

int	parse_inf2(t_data *d, int *i, char *input)
{
	int		j;
	char	*infile;

	*i = go_start_inf2(input, *i);
	j = *i;
	while (input[*i] && ft_isprint(input[*i]) && input[*i] != ' ')
		*i += 1;
	infile = ft_substr(input, j, *i - j);
	if (!infile)
	{
		ft_putstr_fd("error: substr\n", 2);
		g_error = 112;
		return (-1);
	}
	d->cmd->infile_name = infile;
	add_pipe_inf2(d, *i, input);
	if (!d->cmd->exe)
	{
		if (get_cmd(input, d, i) == 1)
			return (-1);
	}
	else
		*i = j;
	return (0);
}

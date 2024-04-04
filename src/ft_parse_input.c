/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:10:00 by mafranco          #+#    #+#             */
/*   Updated: 2024/04/03 16:09:25 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int	get_arg(char *input, int *i, t_data *d, int k)
{
	char	**ret;
	int		start;

	ret = ft_calloc(sizeof(char *), d->cmd->nb_arg + 2);
	if (!ret)
		return (error_msg("error allocating memory for **char\n", 14));
	while (k < d->cmd->nb_arg)
	{
		*i = ft_skip_space(input, *i);
		start = *i;
		*i = ft_go_next_space(input, *i);
		ret[k] = ft_substr_mnsh(input, start, *i - start, d);
		if (!ret[k] && d->flag_err == 1)
		{
			free_arg(ret, k);
			return (0);
		}
		else if (d->flag_err == 3)
			del_arg_empty(d, &k, ret);
		k++;
	}
	ret[k] = NULL;
	d->cmd->arg = ret;
	return (0);
}

int	get_cmd(char *input, t_data *d, int *i)
{
	int	j;

	d->nb_f += 1;
	get_nb_arg(input, *i, d);
	j = get_arg(input, i, d, 0);
	if (j == 1)
		return (1);
	d->cmd->exe = d->cmd->arg[0];
	return (0);
}

int	parse(char *input, t_data *d, int i, int err)
{
	t_cmd	*first;

	(void)err;
	first = d->cmd;
	while (input[i])
	{
		if (get_cmd(input, d, &i) == 1)
			return (free_cmd_parsing(d, first));
		i = ft_skip_space(input, i);
		if (!input[i])
		{
			d->cmd = first;
			return (0);
		}
		get_redirection(input, &i, d);
		d->cmd->next = ft_new_cmd();
		if (d->cmd->next == NULL)
			return (free_newcmd_parsing(d, first));
		d->first = d->cmd;
		d->cmd = d->cmd->next;
	}
	d->cmd = first;
	return (0);
}

int	ft_parse_input(char *input, t_data *d)
{
	if (check_pipe(input, 0, 0, 0) == 1)
		return (1);
	if (check_redir(input) == 1)
		return (1);
	if (check_quotes(input) == 1)
		return (1);
	d->cmd = ft_new_cmd();
	if (d->cmd == NULL)
		return (error_msg("error allocating memory for cmd list\n", 13));
	d->first = d->cmd;
	if (parse(input, d, 0, 0) == 1)
		return (1);
	return (0);
}

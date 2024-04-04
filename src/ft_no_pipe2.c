/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_pipe2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:11:29 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/19 18:14:50 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	free_char(char *to_free, char *to_free2, char *str, int nb)
{
	if (to_free)
		free(to_free);
	if (to_free2)
		free(to_free2);
	perror(str);
	g_error = nb;
}

void	dbl_free(char *s1, char *s2)
{
	free(s1);
	free(s2);
}
/*
void	inf2_solo(int p[2], t_data *d)
{
	char	*line;

	line = readline("> ");
	while (line, )
}*/

/*

void	ft_np_inf2_3(t_data *d, int *p, char *tmp1)
{
	if (!tmp1)
		return (v_err_msg("error strjoin\n", 92));
	free(d->input);
	d->input = tmp1;
	if (dup2(p[0], 0) == -1)
		return (v_err_msg("error dup2\n", 93));
	if (close(p[0]) || close(p[1]))
		return (v_err_msg("error close\n", 94));
}

void	ft_np_inf2_2(t_data *d, int *p, char *line, char *tmp1)
{
	char	*tmp2;
	char	*tmp3;

	while (line && ft_strncmp(line, d->cmd->infile_name,
			ft_strlen(d->cmd->next->exe) + 1))
	{
		write(p[1], line, ft_strlen(line));
		write(p[1], "\n", 1);
		free(line);
		line = readline("> ");
		if (!line)
			return (free_char(tmp1, NULL, "error reading line\n", 89));
		tmp2 = ft_strjoin(ft_strjoin(tmp1, line), "\n");
		free(tmp1);
		if (!tmp2)
			return (free_char(line, NULL, "error strjoin\n", 90));
		tmp1 = tmp2;
	}
	free(line);
	tmp3 = ft_strjoin(d->input, "\n");
	if (!tmp3)
		return (free_char(tmp1, tmp2, "error strjoin\n", 91));
	tmp1 = ft_strjoin(tmp3, tmp2);
	dbl_free(tmp2, tmp3);
	ft_np_inf2_3(d, p, tmp1);
}*/

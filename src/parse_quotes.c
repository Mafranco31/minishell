/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 23:34:57 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/13 01:25:13 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	new_aif(t_qte *qte, int start, int len)
{
	char	*dup_arg;
	char	*dup_new;

	dup_arg = ft_substr(qte->arg, start, len);
	if (!dup_arg)
	{
		qte->flag_err = 1;
		return (return_error_quotes(qte->new, 18));
	}
	dup_new = ft_strdup(qte->new);
	if (!dup_new)
	{
		free(dup_arg);
		qte->flag_err = 1;
		return (return_error_quotes(qte->new, 1));
	}
	free(qte->new);
	qte->new = ft_strjoin(dup_new, dup_arg);
	free(dup_arg);
	free(dup_new);
	if (!qte->new)
	{
		qte->flag_err = 1;
		g_error = 20;
	}
}

char	*add_in_front(t_qte *qte, int start, int len)
{
	if (len > 0 && qte->new)
		new_aif(qte, start, len);
	else if (len > 0)
	{
		qte->new = ft_substr(qte->arg, start, len);
		if (!qte->new)
		{
			qte->flag_err = 1;
			g_error = 21;
		}
	}
	return (qte->new);
}

void	new_aif2(char *arg, t_qte *qte, int start, int len)
{
	char	*dup_arg;
	char	*dup_new;

	dup_arg = ft_substr(arg, start, len);
	if (!dup_arg)
	{
		qte->flag_err = 1;
		return (return_error_quotes(qte->new, 22));
	}
	dup_new = ft_strdup(qte->new);
	if (!dup_new)
	{
		qte->flag_err = 1;
		free(dup_arg);
		return (return_error_quotes(qte->new, 23));
	}
	free(qte->new);
	qte->new = ft_strjoin(dup_new, dup_arg);
	free(dup_arg);
	free(dup_new);
	if (!qte->new)
	{
		g_error = 24;
		qte->flag_err = 1;
	}
}

char	*add_in_front2(char *arg, t_qte *qte, int start, int len)
{
	if (len > 0 && qte->new)
		new_aif2(arg, qte, start, len);
	else if (len > 0)
	{
		qte->new = ft_substr(arg, start, len);
		if (!qte->new)
		{
			g_error = 25;
			qte->flag_err = 1;
		}
	}
	return (qte->new);
}

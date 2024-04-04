/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_minishell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:27:30 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/17 19:45:47 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	gt_dollar(char *dlr, t_data *d, t_qte *qte, int *j)
{
	int	len;
	int	i;
	int	taille;

	taille = ft_strlen(dlr);
	i = 0;
	if (ft_strncmp(dlr, "?", 1) == 0)
	{
		dlr_interrogation(d, qte, j);
		return ;
	}
	while (d->env[i])
	{
		len = 0;
		while (d->env[i][len] && d->env[i][len] != 61)
			len++;
		if (ft_strncmp(dlr, d->env[i], len) == 0 && (len == taille))
		{
			qte->new = add_in_front2(d->env[i], qte, len + 1,
					ft_strlen(d->env[i]) - len - 1);
			return ;
		}
		i++;
	}
	return ;
}

static char	*add_dollar(t_qte *qte, int *i, int start, t_data *d)
{
	*i += 1;
	while (qte->arg[*i] != 34 && qte->arg[*i])
	{
		if (qte->arg[*i] == 36)
		{
			change_dlr_sub(qte, &start, i, d);
			if (qte->flag_err == 1)
				return (NULL);
		}
		else
			*i += 1;
	}
	qte->new = add_in_front(qte, start, *i - start);
	*i += 1;
	return (qte->new);
}

char	*del_simple_quotes(t_qte *qte, int *i, int start_a, t_data *d)
{
	int	start;

	(void)start_a;
	start = *i + 1;
	if (qte->arg[*i] == 39)
	{
		*i = ft_go_next_quote(qte->arg, *i + 1, qte->arg[*i]);
		*i += 1;
		qte->new = add_in_front(qte, start, *i - start - 1);
	}
	else
		qte->new = add_dollar(qte, i, start, d);
	return (qte->new);
}

static void	get_quotes(t_qte *qte, t_data *d)
{
	int		i;
	int		start;

	qte->flag_err = 0;
	i = 0;
	start = 0;
	qte->qte_in = 0;
	while (qte->arg[i])
	{
		qte->qte_in = 0;
		if (qte->arg[i] == 39 || qte->arg[i] == 34)
		{
			is_qte_sub(qte, &start, &i, d);
		}
		else if (qte->arg[i] == 36)
			is_dlr_sub(qte, &start, &i, d);
		else
			i++;
		if (qte->flag_err == 1)
			return ;
	}
	if (i != start)
		qte->qte_in = 0;
	qte->new = add_in_front(qte, start, i - start);
	return ;
}

char	*ft_substr_mnsh(char const *s, unsigned int srt, size_t len, t_data *d)
{
	t_qte	*qte;
	char	*str;

	qte = malloc(sizeof(t_qte) * 1);
	if (!qte)
		return (c_err_msg("error allocating memory for t_qte\n", 15));
	if (srt > ft_strlen(s))
		srt = ft_strlen(s);
	if (len > ft_strlen(s + srt))
		len = ft_strlen(s + srt);
	if (ft_strlen(s) < srt)
		len = 0;
	qte->arg = ft_calloc(sizeof(char), len + 1);
	if (!qte->arg)
		return (c_err_msg("error allocating memory for t_qte->arg\n", 16));
	ft_strlcpy(qte->arg, s + srt, len + 1);
	qte->new = NULL;
	get_quotes(qte, d);
	str = ft_strdup(qte->new);
	if (!str && g_error == 0)
		g_error = 0;
	free_qte(qte, d, str);
	return (str);
}

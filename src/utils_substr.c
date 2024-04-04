/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_substr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:06:34 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/17 00:56:06 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	free_qte(t_qte *qte, t_data *d, char *str)
{
	d->flag_err = qte->flag_err;
	if (!str && qte->flag_err == 0 && qte->qte_in == 0)
		d->flag_err = 2;
	else if (!str && qte->flag_err == 0 && qte->qte_in == 1)
		d->flag_err = 3;
	if (qte->flag_err != 1)
		free(qte->new);
	free(qte->arg);
	free(qte);
}

void	del_arg_empty(t_data *d, int *k, char **ret)
{
	(void)ret;
	d->cmd->nb_arg--;
	*k -= 1;
}

void	change_dlr_sub(t_qte *qte, int *start, int *i, t_data *d)
{
	char	*sub;

	sub = NULL;
	qte->new = add_in_front(qte, *start, *i - *start);
	if (qte->flag_err == 1)
		return ;
	*start = *i + 1;
	if (qte->arg[*i + 1] == 63)
		gt_dollar("?", d, qte, i);
	else
	{
		*i = ft_go_end_dollar(qte->arg, *i + 1);
		sub = ft_substr(qte->arg, *start, *i - *start);
		if (!sub)
			return (cge_dlr_rtrn(qte));
		if (ft_strlen(sub) == 0)
			qte->new = add_in_front2("$", qte, 0, 1);
		else
			gt_dollar(sub, d, qte, i);
		free(sub);
	}
	*start = *i;
}

void	is_dlr_sub(t_qte *qte, int *start, int *i, t_data *d)
{
	if (qte->flag_err == 1)
		return ;
	change_dlr_sub(qte, start, i, d);
	qte->qte_in = 1;
}

void	is_qte_sub(t_qte *qte, int *start, int *i, t_data *d)
{
	qte->new = add_in_front(qte, *start, *i - *start);
	if (qte->flag_err == 1)
		return (v_err_msg("error allocating memory for qte->new\n", 17));
	if (qte->arg[*i + 1] != qte->arg[*i])
	{
		qte->new = del_simple_quotes(qte, i, *start, d);
		if (qte->flag_err == 1)
			return ;
	}
	else
		*i += 2;
	*start = *i;
}

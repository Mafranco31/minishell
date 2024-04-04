/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:01:59 by mafranco          #+#    #+#             */
/*   Updated: 2024/04/03 15:47:53 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	err_chdir(t_data *d)
{
	if (dup2(2, 1) == -1)
		return (v_err_msg("error dup2\n", 97));
	ft_putstr_fd("-bash: cd: ", 2);
	ft_putstr_fd(d->cmd->arg[1], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_error = 1;
	if (dup2(d->tmp_stdout, 1) == -1)
		return (v_err_msg("error dup2\n", 98));
}

char	*cd_before(char *path)
{
	char	*tmp;

	if (ft_strrchr(path, '/') - path == 0)
		tmp = ft_strdup("/");
	else
		tmp = ft_substr(path, 0, (ft_strrchr(path, '/') - path));
	free(path);
	return (tmp);
}

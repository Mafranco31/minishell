/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:06:29 by mafranco          #+#    #+#             */
/*   Updated: 2024/04/03 15:47:29 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	ft_set_env(t_data *d)
{
	int	i;
	int	pwd;
	int	err;

	i = 0;
	pwd = 0;
	err = 0;
	while (d->env[pwd] && ft_strncmp(d->env[pwd], "PWD=", 4))
		pwd++;
	if (!d->env[pwd])
		return ;
	while (d->env[i])
	{
		if (!ft_strncmp(d->env[i], "OLDPWD=", 7))
		{
			err += cd_set_oldpwd(d, pwd, i);
			err += cd_set_pwd(d, pwd);
		}
		if (err > 0)
			return ;
		i++;
	}
	g_error = 0;
}

char	*ft_path(t_data *d, int i, int j)
{
	char	*path;
	char	**arg;

	arg = ft_split(d->cmd->arg[1], '/');
	if (!arg)
		return (c_err_msg("error allocating memory with ft_split\n", 127));
	while (d->env[i] && ft_strncmp(d->env[i], "PWD=", 4) != 0)
		i++;
	path = ft_strdup(d->env[i] + 4);
	if (!path)
		return (c_err_msg("error allocating memory with ft_strdup\n", 44));
	while (arg[j])
	{
		if (!strncmp(arg[j], "..", 3))
			path = cd_before(path);
		else if (strncmp(arg[j], ".", 2))
			path = cd_double_point(path, arg, j);
		if (!path)
			return (free_all_cd_arg(arg, j));
		free(arg[j]);
		j++;
	}
	free(arg);
	return (path);
}

char	*ft_home(t_data *d)
{
	int		i;
	char	*path;

	i = 0;
	while (d->env[i] && ft_strncmp(d->env[i], "HOME=", 5))
		i++;
	if (!d->env[i])
	{
		g_error = 1;
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (NULL);
	}
	path = ft_strdup(d->env[i] + 5);
	if (!path)
		return (c_err_msg("error allocating memory for ft_home\n", 41));
	return (path);
}
/*
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
}*/

char	*ft_oldpwd(t_data *d)
{
	int		i;
	char	*path;

	i = 0;
	while (d->env[i] && ft_strncmp(d->env[i], "OLDPWD=", 7))
		i++;
	if (!d->env[i])
	{
		g_error = 1;
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (NULL);
	}
	path = ft_strdup(d->env[i] + 7);
	if (!path)
		return (c_err_msg("error allocating memory for ft_home\n", 41));
	return (path);
}

void	ft_cd(t_data *d, int i, char *path)
{
	while (d->cmd->arg[i])
		i++;
	if (i > 3)
	{
		g_error = 1;
		ft_putstr_fd(" too many arguments\n", 2);
		return ;
	}
	if ((i == 1 && !d->cmd->arg[1]) || !ft_strncmp(d->cmd->arg[1], "~", 2))
		path = ft_home(d);
	else if (!ft_strncmp(d->cmd->arg[1], "-", 1))
		path = ft_oldpwd(d);
	else if (d->cmd->arg[1][0] == '/')
	{
		path = ft_strdup(d->cmd->arg[1]);
		if (!path && g_error == 0)
			return (v_err_msg("error allocating memory with ft_strdup\n", 42));
	}
	else
		path = d->cmd->arg[1];
	if (!path)
		return ;
	if (chdir(path) == -1)
		return (err_chdir(d));
	ft_set_env(d);
}

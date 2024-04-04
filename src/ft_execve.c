/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:22:31 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/26 13:40:21 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

static char	*err_exec(char *str, char *msg, int nb)
{
	ft_putstr_fd("error: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(msg, 2);
	g_error = nb;
	return (NULL);
}

static char	*exec_path2(t_data *d, char *path)
{
	if (d->cmd->exe && d->cmd->exe[0] == 46 && !d->cmd->exe[1])
		return (err_exec(path, "filename argument required\n", 2));
	else if (d->cmd->exe && d->cmd->exe[0] == 46
		&& d->cmd->exe[1] == 46 && !d->cmd->exe[2])
		return (err_exec(path, "command not found\n", 127));
	else
	{
		path = ft_check_path_ex(d->path, d->cmd, d, 0);
		if (!path)
			return (NULL);
	}
	return (path);
}

static char	*exec_path(t_data *d, char *path)
{
	if (d->cmd->exe && (d->cmd->exe[0] == 47 || (d->cmd->exe[0] == 46
				&& d->cmd->exe[1] == 47)))
	{
		if (!access(d->cmd->exe, F_OK))
		{
			path = ft_strdup(d->cmd->exe);
			if (!path)
				return (c_err_msg("error allocating memory for ft_execve\n",
						68));
			path = is_direct(path);
		}
		else
		{
			if (errno == EACCES)
				return (err_exec(path, "Permission denied\n", 1));
			else if (errno == ENOENT)
				return (err_exec(path, "No such file or directory\n", 127));
		}
		return (path);
	}
	else
		return (exec_path2(d, path));
}

/*
static void	error_exc(int status)
{
	if (status == 256)
		g_error = WEXITSTATUS(status);
	else if (status == 512)
		g_error = 2;
	else if (status == 32512)
	{
		perror(" command not found\n");
		g_error = 127;
	}
	else
		g_error = status;
}
*/
void	ft_execve(t_data *d, char *path)
{
	int		status;
	pid_t	pid;

	path = exec_path(d, path);
	if (!path)
		return ;
	pid = fork();
	wait_signal(0);
	if (pid == -1)
		return (v_err_msg("error fork\n", 69));
	if (pid == 0)
	{
		if (execve(path, d->cmd->arg, d->env) == -1)
			g_error = 63;
		exit(EXIT_FAILURE);
	}
	if (waitpid(pid, &status, 0) == -1)
		return (v_err_msg("error: pid\n", 88));
	g_error = execve_err_nb(status);
	free(path);
}

void	ft_execve2(t_data *d, char *path)
{
	wait_signal(0);
	path = exec_path(d, path);
	if (!path)
		return ;
	if (execve(path, d->cmd->arg, d->env) == -1)
	{
		g_error = 63;
		exit(EXIT_FAILURE);
	}
	free(path);
}

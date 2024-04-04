/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:54:38 by dlitran           #+#    #+#             */
/*   Updated: 2024/03/25 14:00:32 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

static void	*free_error_utils(char *slash, char **matrix, int error, int nb)
{
	int	i;

	i = 0;
	if (slash)
		free(slash);
	if (matrix)
	{
		while (matrix[i])
			i++;
		i--;
		while (i >= 0)
		{
			free(matrix[i]);
			i--;
		}
		free(matrix);
	}
	if (error == 1)
		v_err_msg("error allocating memory for path\n", nb);
	return (NULL);
}

char	*is_direct(char *path)
{
	struct stat	file_stat;

	if (lstat(path, &file_stat) == -1)
	{
		return (c_err_msg("error lstat\n", 99));
	}
	if (S_ISDIR(file_stat.st_mode))
	{
		ft_putstr_fd("error: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(" is a directory\n", 2);
		g_error = 126;
		return (NULL);
	}
	return (path);
}

char	*ft_absolute_path(t_cmd *cmd, t_data *d)
{
	char	*joined;
	char	*slash;
	int		i;

	i = 0;
	slash = ft_strjoin("/", cmd->exe);
	if (!slash)
		return (c_err_msg("error allocating memory with ft_strjoin\n", 66));
	while (d->env[i] && ft_strncmp(d->env[i], "PWD=", 4) != 0)
		i++;
	joined = ft_strjoin(d->env[i] + 4, slash);
	free(slash);
	if (!joined)
		return (c_err_msg("error allocating memory with ft_strjoin\n", 67));
	return (joined);
}

char	*ft_check_path2(char *join, t_cmd *cmd, t_data *d)
{
	join = ft_absolute_path(cmd, d);
	if (!join)
		return (NULL);
	if (!access(join, F_OK))
		return (join);
	free(join);
	if (ft_strncmp(cmd->exe, "./", 2) == 0)
	{
		join = ft_path(d, 0, 0);
		if (!join)
			return (NULL);
		if (!access(join, F_OK))
			return (join);
		free(join);
	}
	ft_putstr_fd("error: ", 2);
	ft_putstr_fd(cmd->exe, 2);
	ft_putstr_fd("command not found\n", 2);
	g_error = 127;
	return (NULL);
}

char	*ft_check_path(char *path, t_cmd *cmd, t_data *d, int i)
{
	char	**matrix;
	char	*slash;
	char	*joined;

	slash = ft_strjoin("/", cmd->exe);
	matrix = ft_split(path, ':');
	if (!matrix || !slash)
		return (free_error_utils(slash, matrix, 1, 64));
	while (matrix[i])
	{
		joined = ft_strjoin(matrix[i], slash);
		if (!joined)
			return (free_error_utils(slash, matrix, 1, 65));
		if (!access(joined, F_OK))
		{
			free_error_utils(slash, matrix, 0, 0);
			return (joined);
		}
		free(joined);
		i++;
	}
	free_error_utils(slash, matrix, 0, 0);
	return (ft_check_path2(joined, cmd, d));
}

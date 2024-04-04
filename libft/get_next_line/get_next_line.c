/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:03:09 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/16 19:21:47 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fd_read(int fd, char *total)
{
	char	*tmp;
	int		chk;

	tmp = my_malloc(BUFFER_SIZE, 1);
	if (!tmp)
		return (0);
	chk = 1;
	while (chk > 0 && !check_char(tmp, '\n'))
	{
		chk = read(fd, tmp, BUFFER_SIZE);
		if (chk > 0)
		{
			tmp [chk] = '\0';
			total = gnl_strjoin(total, tmp);
		}
	}
	free(tmp);
	if (chk == -1)
	{
		free(total);
		return (0);
	}
	return (total);
}

char	*take_line(char *total)
{
	char	*rtrn_buff;
	size_t	size;

	size = 0;
	if (!total[0])
		return (0);
	while (total[size] != '\n' && total[size] != '\0')
		size++;
	if (total[size] == '\n')
		rtrn_buff = gnl_substr(total, 0, size + 1);
	else
		rtrn_buff = gnl_substr(total, 0, size);
	return (rtrn_buff);
}

char	*cut_static(char *total)
{
	size_t	i;
	char	*new_total_buff;

	i = 0;
	while (total[i] != '\n' && total[i] != '\0')
		i++;
	if (total[i] == '\n' && total[i + 1] != '\0')
	{
		i++;
		new_total_buff = gnl_substr(total, i,
				(gnl_strlen(total) - i));
	}
	else
		new_total_buff = NULL;
	free (total);
	if (!new_total_buff)
		return (NULL);
	return (new_total_buff);
}

char	*get_next_line(int fd)
{
	static char	*total;
	char		*return_buff;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	if (!total || (total && !(check_char(total, '\n'))))
		total = fd_read(fd, total);
	if (!total)
		return (0);
	return_buff = take_line(total);
	if (!return_buff)
	{
		free(total);
		return (0);
	}
	total = cut_static(total);
	return (return_buff);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:10:12 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/16 19:19:04 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

char	*my_malloc(size_t nbytes, size_t size);

char	*gnl_substr(const char *total_buff, unsigned int start, size_t len);

char	*gnl_strjoin(char *total_buff, char *tmp);

char	*fd_read(int fd, char *total_buff);

char	*take_line(char *total_buff);

char	*cut_static(char *total_buff);

char	*get_next_line(int fd);

char	*check_char(const char *str, int c);

size_t	gnl_strlen(const char *str);

#endif

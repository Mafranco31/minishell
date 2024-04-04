/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:07:38 by mafranco          #+#    #+#             */
/*   Updated: 2023/05/31 15:21:22 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	destl;
	size_t	srcl;

	destl = ft_strlen(dest);
	srcl = ft_strlen(src);
	j = 0;
	i = destl;
	if (i < size - 1 && size > 0)
	{
		while (destl + j < size - 1 && src[j])
		{
			dest[i] = src[j];
			i++;
			j++;
		}
		dest[i] = 0;
	}
	if (destl >= size)
		destl = size;
	return (destl + srcl);
}

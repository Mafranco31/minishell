/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:38:36 by mafranco          #+#    #+#             */
/*   Updated: 2023/06/01 00:52:00 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*str;
	int		j;
	int		k;

	i = ft_strlen(s1) + ft_strlen(s2);
	str = ft_calloc((i + 1), sizeof(char));
	if (!str)
		return (NULL);
	j = 0;
	k = 0;
	while (s1[j])
	{
		str[j] = *(unsigned char *)(s1 + j);
		j++;
	}
	while (s2[k])
	{
		str[j] = *(unsigned char *)(s2 + k);
		j++;
		k++;
	}
	str[j] = 0;
	return (str);
}

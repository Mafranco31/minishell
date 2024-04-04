/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:42:05 by mafranco          #+#    #+#             */
/*   Updated: 2023/05/31 19:42:04 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*str;
	size_t		debut;
	size_t		fin;

	debut = 0;
	fin = ft_strlen(s1);
	while (ft_strchr(set, s1[debut]) && debut < ft_strlen(s1))
		debut++;
	while (ft_strrchr(set, s1[fin]) && fin > 0)
		fin--;
	str = ft_substr(s1, debut, fin - debut + 1);
	return (str);
}

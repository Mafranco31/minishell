/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:16:13 by mafranco          #+#    #+#             */
/*   Updated: 2023/06/27 21:36:06 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_mkget(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (*s == '\0')
		return (0);
	while (*s != '\0')
	{
		if (*s == c)
			count = 0;
		else if (count == 0)
		{
			count = 1;
			i++;
		}
		s++;
	}
	return (i);
}

static	char	**freethis(const char **ret, int l)
{
	while (l > 0)
	{
		l--;
		free((void *)ret[l]);
	}
	free(ret);
	return (NULL);
}

static	int	numchar(char const *s, char c, int i)
{
	int	lenght;

	lenght = 0;
	while (s[i] != c && s[i] != '\0')
	{
		lenght++;
		i++;
	}
	return (lenght);
}

static	char	**ft_maketable(char **ret, const char *s, char c, int i)
{
	int	j;
	int	k;
	int	l;

	j = 0;
	k = 0;
	while (s[j] != '\0' && k < i)
	{
		l = 0;
		while (s[j] == c)
			j++;
		ret[k] = (char *)malloc(sizeof(char) * numchar(s, c, j) + 1);
		if (ret[k] == NULL)
			return (freethis((char const **)ret, k));
		while (s[j] != '\0' && s[j] != c)
			ret[k][l++] = s[j++];
		ret[k][l] = '\0';
		k++;
	}
	ret[k] = 0;
	return (ret);
}

char	**ft_split(const char *s, char c)
{
	char	**ret;
	int		i;

	if (s == NULL)
		return (NULL);
	i = ft_mkget(s, c);
	ret = malloc(sizeof(char *) * (i + 1));
	if (!ret)
		return (0);
	return (ft_maketable(ret, s, c, i));
}

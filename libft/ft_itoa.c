/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:19:06 by mafranco          #+#    #+#             */
/*   Updated: 2023/06/27 23:00:16 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	getlenght(int n)
{
	int	count;

	if (n == -2147483648)
		return (10);
	if (n < 0)
		n *= -1;
	count = 1;
	while (n > 9)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static	char	*makemaxint(char *nbr)
{
	nbr[1] = '2';
	nbr[2] = '1';
	nbr[3] = '4';
	nbr[4] = '7';
	nbr[5] = '4';
	nbr[6] = '8';
	nbr[7] = '3';
	nbr[8] = '6';
	nbr[9] = '4';
	nbr[10] = '8';
	return (nbr);
}

static	char	*getnum(char *ret, int n, int lenght, int negative)
{
	if (negative == 1)
	{
		ret[0] = 45;
		n *= -1;
	}
	ret[lenght + negative] = '\0';
	if (n == -2147483648)
		ret = makemaxint(ret);
	else
	{
		while (lenght > 0)
		{
			ret[lenght + negative - 1] = (n % 10) + 48;
			n /= 10;
			lenght--;
		}
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		negative;
	int		lenght;

	negative = 0;
	if (n < 0)
		negative = 1;
	lenght = getlenght(n);
	ret = (char *)malloc(lenght + negative + 1);
	if (!ret)
		return (NULL);
	return (getnum(ret, n, lenght, negative));
}

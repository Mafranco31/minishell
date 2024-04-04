/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 00:04:30 by mafranco          #+#    #+#             */
/*   Updated: 2023/06/27 16:17:43 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	resultat;
	int	i;
	int	negative;

	i = 0;
	negative = 1;
	while (nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == '\v'
		|| nptr[i] == '\f' || nptr[i] == '\r' || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
		negative = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	resultat = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		resultat = (resultat * 10) + (nptr[i++] - 48);
	return (resultat * negative);
}

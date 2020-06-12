/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 17:34:18 by vscabell          #+#    #+#             */
/*   Updated: 2020/01/29 09:01:02 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(int nbr)
{
	int		len;
	long	n;

	n = nbr;
	len = 1;
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n / 10 > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	long	nbr;
	char	*itoa;
	int		i;
	int		len;

	nbr = n;
	len = ft_nbrlen(nbr);
	if (!(itoa = malloc((len + 1) * sizeof(char))))
		return (NULL);
	itoa[len] = '\0';
	i = 0;
	if (nbr < 0)
	{
		itoa[i] = '-';
		nbr = nbr * -1;
		i++;
	}
	while (nbr / 10 > 0 && len > i)
	{
		itoa[len - 1] = nbr % 10 + '0';
		nbr = nbr / 10;
		len--;
	}
	itoa[i] = nbr % 10 + '0';
	return (itoa);
}

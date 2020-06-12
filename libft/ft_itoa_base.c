/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 20:03:08 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/10 03:37:04 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(int nbr, int size_base)
{
	int			len;
	long		n;

	n = nbr;
	len = 1;
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n / size_base > 0)
	{
		n = n / size_base;
		len++;
	}
	return (len);
}

char		*ft_itoa_base(int n, char *base, int size_base)
{
	long	nbr;
	char	*itoa;
	int		len;
	int		i;

	len = ft_nbrlen(n, size_base);
	nbr = n;
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
	while (nbr / size_base > 0 && len > i)
	{
		itoa[len - 1] = base[nbr % size_base];
		nbr = nbr / size_base;
		len--;
	}
	itoa[i] = base[nbr % size_base];
	return (itoa);
}

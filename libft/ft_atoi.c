/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:25:28 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/09 18:35:45 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	long	n;
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1 * sign;
		i++;
	}
	if (ft_isdigit(str[i]) == 0)
		return (0);
	n = str[i] - '0';
	i++;
	while (ft_isdigit(str[i]) == 1)
	{
		n = 10 * n + (str[i] - '0');
		i++;
	}
	return (n * sign);
}

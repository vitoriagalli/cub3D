/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:34:19 by vscabell          #+#    #+#             */
/*   Updated: 2020/02/06 18:14:40 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	lenplus;

	lenplus = ft_strlen(s1) + 1;
	if (!(s2 = malloc(lenplus * sizeof(char))))
		return (NULL);
	ft_memcpy(s2, s1, lenplus);
	return (s2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 09:49:24 by vscabell          #+#    #+#             */
/*   Updated: 2020/02/06 18:38:11 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	n_len;

	i = 0;
	n_len = ft_strlen(needle);
	if (needle[i] == '\0')
		return ((char *)&haystack[i]);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (i + j) < len)
		{
			if (j == n_len - 1)
				return ((char *)&haystack[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

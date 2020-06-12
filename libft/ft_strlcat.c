/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 12:22:13 by vscabell          #+#    #+#             */
/*   Updated: 2020/02/06 15:59:52 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t dstlen;

	i = 0;
	dstlen = ft_strlen(dst);
	if (dstsize < dstlen)
		return (ft_strlen(src) + dstsize);
	while (src[i] && (dstlen + i + 1) < dstsize)
	{
		dst[dstlen + i] = ((char *)src)[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (ft_strlen(src) + dstlen);
}

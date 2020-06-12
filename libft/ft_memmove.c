/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 17:45:20 by vscabell          #+#    #+#             */
/*   Updated: 2020/02/06 15:07:53 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*dst_c;
	const char	*src_c;

	i = 0;
	dst_c = dst;
	src_c = src;
	if (!dst && !src)
		return (NULL);
	if (src_c < dst_c)
	{
		i = len;
		while (i > 0)
		{
			i--;
			dst_c[i] = src_c[i];
		}
	}
	else
		ft_memcpy(dst_c, src_c, len);
	return (dst_c);
}

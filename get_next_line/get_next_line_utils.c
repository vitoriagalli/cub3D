/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 10:58:26 by vscabell          #+#    #+#             */
/*   Updated: 2020/03/02 12:38:01 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

void	*ft_memcpy(void *dst, const void *src, int n)
{
	int					i;
	unsigned char		*dst_c;
	const unsigned char	*src_c;

	if (!dst && !src)
		return (dst);
	i = 0;
	dst_c = (unsigned char*)dst;
	src_c = (unsigned char*)src;
	while (i < n)
	{
		dst_c[i] = src_c[i];
		i++;
	}
	return (dst_c);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		lenplus;

	lenplus = ft_strlen(s1) + 1;
	if (!(s2 = malloc(lenplus * sizeof(char))))
		return (NULL);
	ft_memcpy(s2, s1, lenplus);
	return (s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strjoin;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	if (!(strjoin = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		strjoin[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		strjoin[j] = s2[i];
		i++;
		j++;
	}
	strjoin[j] = 0;
	return (strjoin);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	int		i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	i = 0;
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (s[start + i] && len > 0)
	{
		substr[i] = s[start + i];
		i++;
		len--;
	}
	substr[i] = '\0';
	return (substr);
}

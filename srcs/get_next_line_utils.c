/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 10:58:26 by vscabell          #+#    #+#             */
/*   Updated: 2020/03/04 12:47:42 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, int n)
{
	int					i;
	unsigned char		*d;
	const unsigned char *s;

	if (!src && !dst)
		return (NULL);
	i = 0;
	s = (const unsigned char *)src;
	d = (unsigned char *)dst;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*dup;

	len = ft_strlen(s1);
	if (!(dup = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_memcpy(dup, s1, (len + 1));
	return (dup);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	lens1;
	size_t	lens2;
	size_t	i;
	char	*join;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if (!s1 || !s2)
		return (NULL);
	if (!(join = malloc(sizeof(char) * (lens1 + lens2 + 1))))
		return (NULL);
	ft_memcpy(join, s1, lens1);
	i = 0;
	while (s2[i])
	{
		join[lens1 + i] = s2[i];
		i++;
	}
	join[lens1 + i] = '\0';
	return (join);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s || ft_strlen(s) < start)
		return (NULL);
	if (!(sub = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

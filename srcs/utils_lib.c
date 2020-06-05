/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 20:15:21 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/05 18:00:29 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void	*ft_calloc_char(size_t count, char c)
{
	void	*ptr;
	size_t	mem;

	mem = count * sizeof(char);
	if (!(ptr = malloc(mem + 1)))
		return (NULL);
	ft_memset(ptr, c, mem);
	return (ptr);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*p;

	p = b;
	i = 0;
	while (i < len)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strjoin_and_free(char *s1, char *s2)
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
	free(s1);
	free(s2);
	return (join);
}

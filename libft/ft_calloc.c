/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 13:53:11 by vscabell          #+#    #+#             */
/*   Updated: 2020/02/06 10:03:59 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	mem;

	mem = count * size;
	if (!(ptr = malloc(mem)))
		return (NULL);
	ft_memset(ptr, 0, mem);
	return (ptr);
}

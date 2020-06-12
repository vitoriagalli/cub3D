/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 10:10:34 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/10 01:23:58 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

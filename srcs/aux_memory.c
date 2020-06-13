/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_memory.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 23:40:26 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/13 02:32:11 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// VERIFICAR FUNCIONALIDADE
void	*allocate_memory(int sizeof_type)
{
	void	*variable;

	if (!(variable = malloc(sizeof_type * 1)))
		return (NULL);
	return (variable);
}

void	**allocate_dynamic(void **buffer, int size, int m)
{
	void	**new_buffer;
	int		i;

	new_buffer = allocate_memory(size * (m + 2));
	i = 0;
	while (i < m)
	{
		new_buffer[i] = buffer[i];
		i++;
	}
	if (m > 0)
		free(buffer);
	return (new_buffer);
}

void	clean_buffer(void **buffer, int n_arrays)
{
	int i;

	i = 0;
	while (i < n_arrays && buffer[i])
	{
		free(buffer[i]);
		buffer[i] = NULL;
		i++;
	}
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 20:15:21 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/06 19:46:51 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

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

void	*alocate_memory(int sizeof_type)
{
	void	*variable;

	if (!(variable = malloc(sizeof_type * 1)))
		return (NULL);
	return (variable);
}

int		**alocate_buffer(int n_arrays, int n_elem)
{
	int	**buffer;
	int i;

	i = 0;
	buffer = alocate_memory(sizeof(int *) * n_arrays);
	while (i < n_arrays)
	{
		buffer[i] = alocate_memory(sizeof(int) * n_elem);
		i++;
	}
	return (buffer);
}

void	clean_buffer(int **buffer, int n_arrays)
{
	int i;

	i = 0;
	while (i < n_arrays)
	{
		free(buffer[i]);
		buffer[i] = NULL;
		i++;
	}
	free(buffer);
	buffer = NULL;
}

/*
** DEPOIS JUNTAS AS DUAS EM UMA SÓ!!!!
*/
void	clean_buffer_char(char **buffer, int n_arrays)
{
	int i;

	i = 0;
	while (i < n_arrays)
	{
		free(buffer[i]);
		buffer[i] = NULL;
		i++;
	}
	free(buffer);
	buffer = NULL;
}

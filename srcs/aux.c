/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:13 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/12 20:00:57 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * data->size_line + x * (data->bpp / 8));
	dst = data->addr + offset;
	*(unsigned int*)dst = color;
}

float	ft_normalize_angle(float angle)
{
	angle = remainder(angle, 2 * PI);
	if (angle < 0)
		angle += (2 * PI);
	return (angle);
}

int		ray_facing(float angle, int way)
{
	int	up;
	int	down;
	int	left;
	int	right;

	down = (angle > 0 && angle < PI) ? TRUE : FALSE;
	up = !(down) ? TRUE : FALSE;
	left = (angle > PI / 2 && angle < 3 * PI / 2) ? TRUE : FALSE;
	right = !left ? TRUE : FALSE;
	if (way == ray_up)
		return (up);
	else if (way == ray_down)
		return (down);
	else if (way == ray_left)
		return (left);
	else if (way == ray_right)
		return (right);
	return (-1);
}

int		is_end_window(t_map *map, float x, float y)
{
	if (x < 0 || x >= map->n_column * TILE_SIZE || y < 0 || y >= map->n_row * TILE_SIZE)
		return (1);
	return (0);
}

float	dist_btw_points(float x0, float y0, float x1, float y1)
{
	return (sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
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


void	*allocate_memory(int sizeof_type)
{
	void	*variable;

	if (!(variable = malloc(sizeof_type * 1)))
		return (NULL);
	return (variable);
}

int		**allocate_buffer(int n_arrays, int n_elem)
{
	int	**buffer;
	int i;

	i = 0;
	buffer = allocate_memory(sizeof(int *) * n_arrays);
	while (i < n_arrays)
	{
		buffer[i] = allocate_memory(sizeof(int) * n_elem);
		i++;
	}
	return (buffer);
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


int		ft_c_is_in(char c, char *str)
{
	size_t	i;
	size_t	len;

	if (!str)
		return (0);
	if (!*str)
		return (0);
	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

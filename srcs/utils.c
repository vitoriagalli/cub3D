/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:13 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/05 04:53:58 by vscabell         ###   ########.fr       */
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
	angle = remainder(angle, 2 * PI);		//verificar se não é fremainder
	if (angle < 0)
		angle += (2 * PI);
	return (angle);
}

int	ray_facing(float angle, int way)
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

int	is_end_window(t_map *map, float x, float y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (1);
	return (0);
}

float	dist_btw_points(float x0, float y0, float x1, float y1)
{
	return(sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
}

void	ft_swap(int *a, int *b)
{
	int aux;

	aux = *a;
	*a = *b;
	*b = aux;
}

void	*alocate_memory(int sizeof_type)
{
	void	*variable;

	if (!(variable = malloc(sizeof_type * 1)))
		return (NULL);
	return (variable);
}

int	**alocate_buffer(int n_arrays, int n_elem)
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


/// DEPOIS JUNTAS AS DUAS EM UMA SÓ!!!!
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

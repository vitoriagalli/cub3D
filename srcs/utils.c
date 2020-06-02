/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:13 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/02 02:03:11 by vscabell         ###   ########.fr       */
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

void	*alocate_memory(int sizeof_type)
{
	void	*variable;

	if (!(variable = malloc(sizeof_type * 1)))
		return (NULL);
	return (variable);
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

	down = (angle > 0 && angle < PI) ? 1 : 0;
	up = !(down) ? 1 : 0;
	left = (angle > PI / 2 && angle < 3 * PI / 2) ? 1 : 0;
	right = !left ? 1 : 0;
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

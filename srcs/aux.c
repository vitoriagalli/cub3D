/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:13 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/13 00:15:52 by vscabell         ###   ########.fr       */
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
	if (x < 0 || x >= map->n_column * TILE_SIZE ||
		y < 0 || y >= map->n_row * TILE_SIZE)
		return (1);
	return (0);
}

float	dist_btw_points(float x0, float y0, float x1, float y1)
{
	return (sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
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

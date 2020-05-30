/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:38 by vscabell          #+#    #+#             */
/*   Updated: 2020/05/30 16:32:06 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map[N_ROW][N_COLUMN] =
{
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};


void	put_map(t_data *img, t_point *point)
{
	int i = 0;
	int j = 0;
	int x0;

	x0 = point->x;
	while (i < N_ROW)
	{
		j = 0;
		point->x = x0;
		while (j < N_COLUMN)
		{
			point->color = map[i][j]> 0? 0xff000029 : 0xdcdcdcfc;
			ft_rectangle(img, *point, TILE_SIZE * MAP2D_SCALE, TILE_SIZE * MAP2D_SCALE);
			point->x = point->x + TILE_SIZE * MAP2D_SCALE;
			j++;
		}
		point->y = point->y + TILE_SIZE * MAP2D_SCALE;
		i++;
	}
	point->x = 0;
	point->y = 0;
}

int	is_wall(int x, int y)
{
	int	grid_x;
	int	grid_y;

	if (x < TILE_SIZE || x > (WIDTH - TILE_SIZE)|| y < TILE_SIZE || y > (HEIGHT - TILE_SIZE))
		return (1);
	grid_x = floor(x / TILE_SIZE);
	grid_y = floor(y / TILE_SIZE);
	if (map[grid_y][grid_x] != 0)
		return(1);
	return(0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:38 by vscabell          #+#    #+#             */
/*   Updated: 2020/05/31 07:55:14 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_grid[13][20] =
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
	{1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};



void	put_map(t_vars *vars)
{
	int i = 0;
	int j = 0;
	int x0;

	x0 = vars->point->x;
	while (i < vars->map->n_row)
	{
		j = 0;
		vars->point->x = x0;
		while (j < vars->map->n_column)
		{
			vars->point->color = map_grid[i][j]> 0? 0xff000029 : 0xdcdcdcfc;
			ft_rectangle(vars->data, *vars->point, vars->map->tile_size * MAP2D_SCALE, vars->map->tile_size * MAP2D_SCALE);
			vars->point->x = vars->point->x + vars->map->tile_size * MAP2D_SCALE;
			j++;
		}
		vars->point->y = vars->point->y + vars->map->tile_size * MAP2D_SCALE;
		i++;
	}
	vars->point->x = 0;
	vars->point->y = 0;
}

int	is_wall(t_map *map, int x, int y)
{
	int	grid_x;
	int	grid_y;

	if (is_end_window(map, x, y))
		return (1);
	grid_x = floor(x / map->tile_size);
	grid_y = floor(y / map->tile_size);
	if (map_grid[grid_y][grid_x] != 0)
		return(1);
	return(0);
}

t_map	*create_map(void)
{
	t_map *map;

	map = alocate_memory(sizeof(t_map));

	map->width = 1000;
	map->height = 650;
	map->n_column = 20;
	map->n_row = 13;
	map->posit_player = create_point(map->width / 2, map->height / 2, 0xff00ffff);
	map->rotation_angle = NORTH;
	map->tile_size = map->width / map->n_column;
	map->num_rays = map->width / WALL_WIDTH;

	return (map);
}

// read the map given
// store the information in the variables
void	read_map(t_vars *vars)
{
	vars->map = create_map();
}


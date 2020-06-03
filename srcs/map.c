/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:38 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/03 20:23:58 by vscabell         ###   ########.fr       */
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
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void	put_minimap(t_vars *vars)
{
	int i;
	int j;
	int x0;

	i = 0;
	x0 = vars->point->x;
	while (i < vars->map->n_row)
	{
		j = 0;
		vars->point->x = x0;
		while (j < vars->map->n_column)
		{
			vars->point->color = map_grid[i][j] > 0 ? WALL_2D_COLOR : VOID_2D_COLOR;
			ft_rectangle(vars->data, *vars->point, vars->map->tile_size * MAP2D_SCALE, vars->map->tile_size * MAP2D_SCALE);
			vars->point->x = vars->point->x + vars->map->tile_size * MAP2D_SCALE;
			j++;
		}
		vars->point->y = vars->point->y + vars->map->tile_size * MAP2D_SCALE;
		i++;
	}
	assign_point(vars->point, 0, 0, 0);
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
		return (1);
	return (0);
}

t_map	*assign_map(void)
{
	t_map *map;

	map = alocate_memory(sizeof(t_map));
	map->width = 1000;
	map->height = 650;
	map->n_column = 20;
	map->n_row = 13;
	map->init_posit = create_point(map->width / 2, map->height / 2, 0);
	map->rotation_angle = NORTH;
	map->tile_size = map->width / map->n_column;
	map->num_rays = map->width / WALL_WIDTH;
	map->color = alocate_memory(sizeof(t_color));
	map->color->ceilling = ft_rgb(0,255,255);
	map->color->floor = ft_rgb(200,200,80);
	map->path = alocate_memory(sizeof(char *) * 4);
	map->path[north] = "./img/wood.xpm";
	map->path[south] = "./img/eagle.xpm";
	map->path[east] = "./img/greystone.xpm";
	map->path[west] = "./img/purplestone.xpm";
	return (map);
}

void	read_map(t_vars *vars)
{
	vars->map = assign_map();
}

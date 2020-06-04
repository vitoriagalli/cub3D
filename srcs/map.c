/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:38 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/04 20:04:50 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// char	map_grid[13][20] =
// {
// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
// 	{1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// };

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
			vars->point->color = vars->map->map_grid[i][j] == '1' ? WALL_2D_COLOR : VOID_2D_COLOR;
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
		return (TRUE);
	grid_x = floor(x / map->tile_size);
	grid_y = floor(y / map->tile_size);
	if (map->map_grid[grid_y][grid_x] == '1')
		return (TRUE);
	return (FALSE);
}

void	assign_map(t_map *map)
{
	// map->map_grid = map_grid;
	// map->width = 1000;
	// map->height = 650;
	// map->n_column = 20;
	// map->n_row = 13;

	// map->init_posit = create_point(map->width / 2, map->height / 2, 0);
	// map->rotation_angle = NORTH;

	map->tile_size = map->width / map->n_column;


	map->init_posit->x = map->init_posit->x * map->n_column + map->tile_size;
	map->init_posit->y = map->init_posit->y * map->n_row + map->tile_size;

	map->num_rays = map->width / WALL_WIDTH;
	// map->color->ceilling = ft_rgb(0,255,255);
	// map->color->floor = ft_rgb(200,200,80);
	// map->path[north] = "./img/wood.xpm";
	// map->path[south] = "./img/bluestone.xpm";
	// map->path[east] = "./img/greystone.xpm";
	// map->path[west] = "./img/redbrick.xpm";
}

void	alocate_map(t_vars *vars)
{
	vars->map = alocate_memory(sizeof(t_map));
	vars->map->color = alocate_memory(sizeof(t_color));
	vars->map->path = alocate_memory(sizeof(char *) * 4);
}

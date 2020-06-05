/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:38 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/05 21:28:30 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_minimap(t_vars *vars)
{
	int i;
	int j;
	int x0;

	i = 0;
	j = 0;
	x0 = vars->point->x;
	while (i < vars->map->n_row)   ///  REVER REVIFICAÇÃO
	{
		j = 0;
		vars->point->x = x0;
		while (j < vars->map->n_column && vars->map->map_grid[i][j])
		{
			if (vars->map->map_grid[i][j] != ' ')
			{
				vars->point->color = vars->map->map_grid[i][j] == '1' ? WALL_2D_COLOR : VOID_2D_COLOR;
				ft_rectangle(vars->data, *vars->point, vars->map->tile_size * MAP2D_SCALE, vars->map->tile_y * MAP2D_SCALE);
			}
			vars->point->x = vars->point->x + vars->map->tile_size * MAP2D_SCALE;
			j++;
		}
		vars->point->y = vars->point->y + vars->map->tile_y * MAP2D_SCALE;
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
	grid_y = floor(y / map->tile_y);
	if (grid_x >= map->n_column || grid_y >= map->n_row)
		return (TRUE);
	if (map->map_grid[grid_y][grid_x] == '1')
		return (TRUE);
	return (FALSE);
}

void	assign_map(t_map *map)
{
	map->tile_size = map->width / map->n_column;						// verificar
	map->tile_y = map->height / map->n_row;						// verificar
	map->init_posit->x = map->init_posit->x * map->tile_size + 1;
	map->init_posit->y = map->init_posit->y * map->tile_y + 1;
	map->num_rays = map->width / WALL_WIDTH;			//VERIFICAAAAAR!!
}

void	alocate_map(t_vars *vars)
{
	vars->map = alocate_memory(sizeof(t_map));
	vars->map->init_posit = NULL;
	vars->map->color = alocate_memory(sizeof(t_color));
	vars->map->color->ceilling = -1;
	vars->map->color->ceilling = -1;
	vars->map->path = alocate_memory(sizeof(char *) * 4);
	vars->map->path[north] = NULL;
	vars->map->path[south] = NULL;
	vars->map->path[east] = NULL;
	vars->map->path[west] = NULL;
	vars->map->init_posit = NULL;
	vars->map->width = 0;
	vars->map->height = 0;
	vars->mlx = NULL;
}

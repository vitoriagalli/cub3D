/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:38 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/11 21:35:31 by vscabell         ###   ########.fr       */
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
	while (i < vars->map->n_row)
	{
		j = 0;
		vars->point->x = x0;
		while (j < vars->map->n_column && vars->map->map_grid[i][j])
		{
			if (vars->map->map_grid[i][j] != ' ')
			{
				vars->point->color = vars->map->map_grid[i][j] == '1' ? WALL_2D_COLOR : VOID_2D_COLOR;
				vars->point->color = vars->map->map_grid[i][j] == '2' ? SPRITE_2D_COLOR : vars->point->color;
				ft_rectangle(vars->data, *vars->point, TILE_SIZE * MAP2D_SCALE, TILE_SIZE * MAP2D_SCALE);
			}
			vars->point->x = vars->point->x + TILE_SIZE * MAP2D_SCALE;
			j++;
		}
		vars->point->y = vars->point->y + TILE_SIZE * MAP2D_SCALE;
		i++;
	}
	assign_point(vars->point, 0, 0, 0);
}

int	is_wall(t_map *map, int x, int y, char identf)
{
	int	grid_x;
	int	grid_y;

	if (is_end_window(map, x, y))
		return (TRUE);
	grid_x = floor(x / TILE_SIZE);
	grid_y = floor(y / TILE_SIZE);
	if (grid_x >= map->n_column || grid_y >= map->n_row)
		return (TRUE);
	if (map->map_grid[grid_y][grid_x] == identf)
		return (TRUE);
	return (FALSE);
}

void	assign_map(t_map *map)
{
	map->init_posit->x = map->init_posit->x * TILE_SIZE + 1;
	map->init_posit->y = map->init_posit->y * TILE_SIZE + 1;
	map->num_rays = map->width / WALL_WIDTH;
}

void	alocate_map(t_vars *vars)
{
	vars->map = alocate_memory(sizeof(t_map));
	vars->map->init_posit = NULL;
	vars->map->color = alocate_memory(sizeof(t_color));
	vars->map->color->ceilling = -1;
	vars->map->color->ceilling = -1;
	vars->map->path = alocate_memory(sizeof(char *) * 5);
	vars->map->path[north] = NULL;
	vars->map->path[south] = NULL;
	vars->map->path[east] = NULL;
	vars->map->path[west] = NULL;
	vars->map->path[sprite] = NULL;
	vars->map->init_posit = NULL;
	vars->map->n_sprites = 0;

	// vars->map->sprite_posit = alocate_memory(sizeof(t_point *) * 4); //por ex num de sprites alocar dyn depois

	// vars->map->sprite_posit[0] = NULL;
	// vars->map->sprite_posit[1] = NULL;
	// vars->map->sprite_posit[2] = NULL;
	// vars->map->sprite_posit[3] = NULL;

	vars->map->width = 0;
	vars->map->height = 0;
	vars->map->n_row = 0;
	vars->map->n_column = 0;
	vars->mlx = NULL;
}

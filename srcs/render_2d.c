/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 23:51:07 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/15 02:43:48 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_rays(t_vars *vars)
{
	int	posit[2];
	int	collision[2];
	int i;

	i = 0;
	while (i < vars->map->num_rays)
	{
		posit[0] = vars->player->posit->x * MAP2D_SCALE;
		posit[1] = vars->player->posit->y * MAP2D_SCALE;
		collision[0] = vars->ray[i]->collision->x * MAP2D_SCALE;
		collision[1] = vars->ray[i]->collision->y * MAP2D_SCALE;
		ft_line(vars->data, posit, collision, vars->player->posit->color);
		i++;
	}
}

void	put_minimap(t_vars *vars)
{
	int i;
	int j;
	int x0;

	i = -1;
	x0 = vars->point->x;
	while (++i < vars->map->n_row)
	{
		j = -1;
		vars->point->x = x0;
		while (++j < vars->map->n_column && vars->map->map_grid[i][j])
		{
			if (vars->map->map_grid[i][j] != ' ')
			{
				vars->point->color = vars->map->map_grid[i][j] == '1' ?
				WALL_2D_COLOR : VOID_2D_COLOR;
				vars->point->color = vars->map->map_grid[i][j] == '2' ?
				SPRITE_2D_COLOR : vars->point->color;
				ft_rectangle(vars->data, *vars->point,
				TILE_SIZE * MAP2D_SCALE, TILE_SIZE * MAP2D_SCALE);
			}
			vars->point->x = vars->point->x + TILE_SIZE * MAP2D_SCALE;
		}
		vars->point->y = vars->point->y + TILE_SIZE * MAP2D_SCALE;
	}
	assign_point(vars->point, 0, 0, 0);
}

int		is_wall(t_map *map, int x, int y, char identf)
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

int		is_end_window(t_map *map, double x, double y)
{
	if (x < 0 || x >= map->n_column * TILE_SIZE ||
		y < 0 || y >= map->n_row * TILE_SIZE)
		return (1);
	return (0);
}

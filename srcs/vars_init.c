/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:38 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/17 04:47:37 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	allocate_map(t_vars *vars)
{
	vars->map = ft_calloc(1, sizeof(t_map));
	vars->map->init_posit = NULL;
	vars->map->color = ft_calloc(1, sizeof(t_color));
	vars->map->color->ceilling = -1;
	vars->map->color->ceilling = -1;
	vars->map->path = ft_calloc(5, sizeof(char *));
	vars->map->path[north] = NULL;
	vars->map->path[south] = NULL;
	vars->map->path[east] = NULL;
	vars->map->path[west] = NULL;
	vars->map->path[sprite] = NULL;
	vars->map->init_posit = NULL;
	vars->map->sprite_posit = NULL;
	vars->map->map_grid = NULL;
	vars->map->n_sprites = 0;
	vars->map->width = 0;
	vars->map->height = 0;
	vars->map->n_row = 0;
	vars->map->n_column = 0;
	vars->mlx = NULL;
}

int		create_n_check(t_vars *vars)
{
	if (!(vars->mlx = mlx_init()))
		return (ft_error(vars->map, -16));
	vars->win = mlx_new_window(vars->mlx, vars->map->width,
				vars->map->height, "CUB3D");
	if (!(vars->tex = create_texture(vars->mlx, vars->map->path)))
		return (ft_path_error(vars));
	vars->data = create_image(vars->mlx, vars->map);
	vars->point = create_point(0, 0, 0);
	vars->player = create_player(vars->map, MOVE_SPEED, ROTAT_SPEED);
	vars->sprite = create_sprite(vars->map);
	vars->minimap = TRUE;
	return (1);
}

void	assign_point(t_point *point, int x, int y, int color)
{
	point->x = x;
	point->y = y;
	point->color = color;
}

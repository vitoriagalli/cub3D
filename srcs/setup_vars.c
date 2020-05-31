/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:03:57 by vscabell          #+#    #+#             */
/*   Updated: 2020/05/31 02:31:48 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_vars(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, vars->map->width, vars->map->height, "map 2d");
	vars->data = create_image(vars->mlx, vars->map);
	vars->point = create_point(0, 0, 0xFF00FFFF);  //point to crate the map
	vars->player = create_player(vars->map, 0xFF00FFFF, 10, 10 * PI / 180);
}

void	setup_vars(t_vars *vars)
{
	read_map(vars);
	create_vars(vars);
	put_map(vars);
	put_player(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:03:57 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/02 02:44:49 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_vars(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, vars->map->width, vars->map->height, "MAP");
	vars->data = create_image(vars->mlx, vars->map);
	vars->point = create_point(0, 0, 0);
	vars->player = create_player(vars->map, MOVE_SPEED, ROTAT_SPEED);
}

void	put_game(t_vars *vars)
{
	vars->ray = ft_raycast(vars);
	put_player_3dmap(vars);
	put_minimap(vars);
	put_player_minimap(vars);
	clean_structure(vars);
}

void	init_game(t_vars *vars)
{
	read_map(vars);
	create_vars(vars);
	put_game(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);
}

int	close_program(t_vars *vars)
{
	free(vars->map->color);
	free(vars->map);
	free(vars->point);
	free(vars->player->posit);
	free(vars->player);
	mlx_destroy_image(vars->mlx, vars->data->img);
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

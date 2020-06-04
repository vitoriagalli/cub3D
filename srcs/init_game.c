/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:03:57 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/04 07:41:50 by vscabell         ###   ########.fr       */
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
	vars->tex = create_texture(vars->mlx, vars->map->path);
	vars->minimap = TRUE;
}

void	put_game(t_vars *vars)
{
	vars->ray = ft_raycast(vars);
	put_player_3dmap(vars);
	if (vars->minimap == TRUE)
	{
		put_minimap(vars);
		put_player_minimap(vars);
	}
	clean_structure(vars);
}

void	init_game(t_vars *vars)
{
	// read_map(vars);		/////////////////
	create_vars(vars);
	put_game(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);
}

int	close_program(t_vars *vars)
{
	free(vars->map->path);
	free(vars->map->color);
	free(vars->map);
	free(vars->point);
	free(vars->player->posit);
	free(vars->player);
	mlx_destroy_image(vars->mlx, vars->tex[north]->data->img);
	mlx_destroy_image(vars->mlx, vars->tex[south]->data->img);
	mlx_destroy_image(vars->mlx, vars->tex[east]->data->img);
	mlx_destroy_image(vars->mlx, vars->tex[west]->data->img);
	free(vars->tex[north]->data);
	free(vars->tex[south]->data);
	free(vars->tex[east]->data);
	free(vars->tex[west]->data);
	free(vars->tex[north]);
	free(vars->tex[south]);
	free(vars->tex[east]);
	free(vars->tex[west]);
	free(vars->tex);
	mlx_destroy_image(vars->mlx, vars->data->img);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

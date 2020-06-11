/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:03:57 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/11 21:40:34 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_vars *vars)
{
	create_vars(vars);
	put_game(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);
}

void	create_vars(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, vars->map->width,
				vars->map->height, "MAP");
	vars->data = create_image(vars->mlx, vars->map);
	vars->point = create_point(0, 0, 0);
	vars->player = create_player(vars->map, MOVE_SPEED, ROTAT_SPEED);
	vars->tex = create_texture(vars->mlx, vars->map->path);
	vars->sprite = create_sprite(vars->map);
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
	clean_ray_struct(vars);
}

void	clean_ray_struct(t_vars *vars)
{
	int i;

	i = 0;
	while (i < vars->map->num_rays)
	{
		free(vars->ray[i]->collision);
		vars->ray[i]->collision = NULL;
		free(vars->ray[i]);
		vars->ray[i] = NULL;
		i++;
	}
	free(vars->ray);
	vars->ray = NULL;
}

int		close_program(t_vars *vars)
{
	clean_buffer((void **)vars->map->map_grid, vars->map->n_row);
	free(vars->map->path[north]);
	free(vars->map->path[south]);
	free(vars->map->path[east]);
	free(vars->map->path[west]);
	free(vars->map->path[sprite]);
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
	mlx_destroy_image(vars->mlx, vars->tex[sprite]->data->img);
	free(vars->tex[north]->data);
	free(vars->tex[south]->data);
	free(vars->tex[east]->data);
	free(vars->tex[west]->data);
	free(vars->tex[sprite]->data);
	free(vars->tex[north]);
	free(vars->tex[south]);
	free(vars->tex[east]);
	free(vars->tex[west]);
	free(vars->tex[sprite]);
	free(vars->tex);

	// dar free na estrutura do sprite????

	mlx_destroy_image(vars->mlx, vars->data->img);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

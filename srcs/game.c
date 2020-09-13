/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:03:57 by vscabell          #+#    #+#             */
/*   Updated: 2020/07/28 03:34:47 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		put_game(t_vars *vars)
{
	ft_raycast(vars);
	put_3dmap(vars);
	put_sprites(vars);
	if (vars->minimap == TRUE)
	{
		put_minimap(vars);
		put_rays(vars);
	}
}

int			init_game(t_vars *vars, int argc)
{
	vars->ray = allocate_ray(vars);
	put_game(vars);
	if (argc == 2)
	{
		vars->win = mlx_new_window(vars->mlx, vars->map->width,
				vars->map->height, "CUB3D ::: by vscabell ::: 42 SP");
		mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);
	}
	else
	{
		save_bmp_file(vars);
		clean_before_close(vars);
	}
	return (0);
}

int			clean_before_close(t_vars *vars)
{
	free_rays(vars);
	free_sprite(vars);
	free_tex(vars->mlx, vars->tex);
	free_buffer((void **)vars->map->map_grid, vars->map->n_row);
	free_buffer((void **)vars->map->path, 5);
	free(vars->map);
	free(vars->point);
	free(vars->player->posit);
	free(vars->player);
	mlx_destroy_image(vars->mlx, vars->data->img);
	free(vars->data);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	free(vars->mlx);
	return (close_program());
}

void		free_rays(t_vars *vars)
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

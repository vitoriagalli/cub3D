/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:03:57 by vscabell          #+#    #+#             */
/*   Updated: 2020/07/01 17:05:57 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_vars *vars, int argc)
{
	put_game(vars);
	if (argc == 2)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);
	else
	{
		render_bmp(vars);
		close_program();
	}
}

void	put_game(t_vars *vars)
{
	vars->ray = ft_raycast(vars);
	put_3dmap(vars);
	put_sprites(vars);
	if (vars->minimap == TRUE)
	{
		put_minimap(vars);
		put_rays(vars);
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

int		clean_before_close(t_vars *vars)
{
	clean_buffer((void **)vars->map->map_grid, vars->map->n_row);
	clean_buffer((void **)vars->map->path, 5);
	free_tex(vars->mlx, vars->tex);
	free(vars->map->color);
	free(vars->map);
	free(vars->point);
	free(vars->player->posit);
	free(vars->player);
	mlx_destroy_image(vars->mlx, vars->data->img);
	mlx_destroy_window(vars->mlx, vars->win);
	return (close_program());
}

int		close_program(void)
{
	exit(0);
	return (0);
}

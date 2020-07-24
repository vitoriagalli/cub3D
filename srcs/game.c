/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:03:57 by vscabell          #+#    #+#             */
/*   Updated: 2020/07/24 22:27:56 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_ray	**allocate_ray(t_vars *vars)
{
	t_ray	**ray;
	int		i;

	i = 0;
	ray = ft_calloc(vars->map->num_rays, sizeof(t_ray *));
	while (i < vars->map->num_rays)
	{
		ray[i] = ft_calloc(1, sizeof(t_ray));
		ray[i]->collision = ft_calloc(1, sizeof(t_point));
		i++;
	}
	return (ray);
}

static void	clean_ray_struct(t_vars *vars)
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

static void	verify_resolution(t_vars *vars)
{
	int	max_display_width;
	int	max_display_height;

	mlx_get_screen_size(vars->mlx, &max_display_width, &max_display_height);
	vars->map->width = vars->map->width > max_display_width ?
						max_display_width : vars->map->width;
	vars->map->height = vars->map->height > max_display_height ?
						max_display_height : vars->map->height;
	vars->map->num_rays = vars->map->width / WALL_WIDTH;
}

int			init_game(t_vars *vars, int argc)
{
	vars->ray = allocate_ray(vars);
	if (argc == 2)
	{
		verify_resolution(vars);
		put_game(vars);
		vars->win = mlx_new_window(vars->mlx, vars->map->width,
				vars->map->height, "CUB3D");
		mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);
	}
	else
	{
		put_game(vars);
		save_bmp_file(vars);
		close_program();
	}
	return (0);
}

int			clean_before_close(t_vars *vars)
{
	clean_ray_struct(vars);
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

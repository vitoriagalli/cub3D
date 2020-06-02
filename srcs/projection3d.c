/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 02:57:12 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/02 01:58:35 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	project_things(t_vars *vars, float wall_proj_height, int i)
{
	t_point	*thing;
	int		color;
	float	ceilling_lim;
	float	wall_lim;
	int 	x;
	int 	y;

	thing = create_point(0, 0, 0);
	ceilling_lim = (vars->map->height / 2) - (wall_proj_height / 2);
	wall_lim = (vars->map->height / 2) + (wall_proj_height / 2);
	x = i * WALL_WIDTH;
	while (x < (i + 1) * WALL_WIDTH)
	{
		y = 0;
		while (y < vars->map->height)
		{
			if (y > 0 && y < ceilling_lim)
				color = vars->map->color->ceilling;
			else if (y >= ceilling_lim && y < wall_lim)
				color = get_color(vars->ray[i], vars->map->color);
			else
			 	color = vars->map->color->floor;
			my_mlx_pixel_put(vars->data, x, y, color);
			y++;
		}
		x++;
	}
	free(thing);
}

void		iterate_3dprojection(t_vars *vars)
{
	float	correct_dist_plane;
	float	dist_proj_plane;
	float	wall_proj_height;
	int		i;

	i = 0;
	dist_proj_plane = (vars->map->width / 2) / (tan(FOV / 2));
	while (i < vars->map->num_rays)
	{
		correct_dist_plane = vars->ray[i]->dist_wall * cos(vars->ray[i]->ray_angle - vars->player->rotation_angle);
		wall_proj_height = (vars->map->tile_size / correct_dist_plane) * dist_proj_plane;
		wall_proj_height = (wall_proj_height < vars->map->height) ? wall_proj_height : vars->map->height;
		project_things(vars, wall_proj_height, i);
		i++;
	}
}

void		put_player_3dmap(t_vars *vars)
{
	iterate_3dprojection(vars);
}

void	clean_structure(t_vars *vars)
{
	int i;

	i = 0;
	while (i < vars->map->num_rays)
	{
		free(vars->ray[i]->collision);
		free(vars->ray[i]);
		i++;
	}
	free(vars->ray);
}

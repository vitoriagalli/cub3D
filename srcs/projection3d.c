/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 02:57:12 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/01 19:22:23 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		projection(t_vars *vars)
{
	t_point	*wall;
	int		i;
	float	correct_dist_plane;
	float	dist_proj_plane;
	float	wall_proj_height;

	wall = create_point(0, 0, 0);
	dist_proj_plane = (vars->map->width / 2) / (tan(FOV / 2));
	i = 0;
	while (i < vars->map->num_rays)
	{
		correct_dist_plane = vars->ray[i]->dist_wall * cos(vars->ray[i]->ray_angle - vars->player->rotation_angle);
		wall_proj_height = (vars->map->tile_size / correct_dist_plane) * dist_proj_plane;
		wall_proj_height = (wall_proj_height < vars->map->height) ? wall_proj_height : vars->map->height;
		assign_point(wall, i * WALL_WIDTH, (vars->map->height / 2) - (wall_proj_height / 2), shade_wall(vars->ray[i]->dist_wall, 255, 255, 255));
		ft_rectangle(vars->data, *wall, WALL_WIDTH, wall_proj_height);
		free(vars->ray[i]->collision);
		free(vars->ray[i]);
		i++;
	}
	free(wall);
}

void		map3d_player(t_vars *vars)
{
	projection(vars);
	free(vars->ray);
}

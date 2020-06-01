/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 02:57:12 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/01 04:34:43 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		projection(t_vars *vars, t_ray *ray)
{
	t_point	*wall;
	int		i;
	float	dist_proj_plane;
	float	wall_proj_height;

	wall = create_point(0, 0, 0);
	dist_proj_plane = (vars->map->width / 2) / (tan(FOV / 2));
	dist_proj_plane *= cos(ray->ray_angle - vars->player->rotation_angle);
	i = 0;
	while (i < vars->map->num_rays)
	{
		wall_proj_height = (vars->map->tile_size / ray->dist_wall) * dist_proj_plane;
		wall_proj_height = (wall_proj_height < vars->map->height) ? wall_proj_height : vars->map->height;
		assign_point(wall, i * WALL_WIDTH, (vars->map->height / 2) - (wall_proj_height / 2), 0xFFFFFFFF);
		ft_rectangle(vars->data, *wall, WALL_WIDTH, wall_proj_height);
		i++;
	}
	free(wall);
	free(ray->collision);
}

void		map3d_player(t_vars *vars)
{
	projection(vars, *vars->ray);
	free(vars->ray);
}

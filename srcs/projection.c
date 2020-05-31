/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 16:39:57 by vscabell          #+#    #+#             */
/*   Updated: 2020/05/31 02:18:13 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	do_projection(t_vars *vars, float *rays)
{
	int		i;
	t_point	*p0;
	float	dist_proj_plane;
	float	wall_proj_height;

	p0 = create_point(0, 0, 0xFFFFFFFF);
	dist_proj_plane = (vars->map->width / 2) / (tan(FOV / 2));
	i = 0;
	while (i < vars->map->num_rays)
	{
		wall_proj_height = (vars->map->tile_size / rays[i]) * dist_proj_plane;
		wall_proj_height = (wall_proj_height < vars->map->height) ? wall_proj_height : vars->map->height;
		assign_point(p0, i * WALL_WIDTH, (vars->map->height / 2) - (wall_proj_height / 2), p0->color);

		ft_rectangle(vars->data, *p0, WALL_WIDTH, wall_proj_height);
		i++;
	}
	free(rays);
	free(p0);
}

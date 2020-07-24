/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 00:19:46 by vscabell          #+#    #+#             */
/*   Updated: 2020/07/24 21:14:45 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	assign_ray(t_ray *ray, t_point *collis, double dist_wall, int coord)
{
	ray->collision->x = collis->x;
	ray->collision->y = collis->y;
	ray->dist_wall = dist_wall;
	ray->coord = coord;
}

static void	check_closest_wall(t_vars *vars, t_ray *ray, double ray_angle)
{
	t_point	horz_intercept;
	t_point	vert_intercept;
	double	dist_horz;
	double	dist_vert;

	cast_ray(vars, ray_angle, HORZ, &horz_intercept);
	cast_ray(vars, ray_angle, VERT, &vert_intercept);
	dist_horz = is_end_window(vars->map, horz_intercept.x, horz_intercept.y) ?
	INT_MAX : dist_btw_points(vars->player->posit->x, vars->player->posit->y,
	horz_intercept.x, horz_intercept.y);
	dist_vert = is_end_window(vars->map, vert_intercept.x, vert_intercept.y) ?
	INT_MAX : dist_btw_points(vars->player->posit->x, vars->player->posit->y,
	vert_intercept.x, vert_intercept.y);
	if (dist_horz < dist_vert)
		assign_ray(ray, &horz_intercept, dist_horz, HORZ);
	else
		assign_ray(ray, &vert_intercept, dist_vert, VERT);
}

int			**ft_raycast(t_vars *vars)
{
	int		i;

	i = 0;
	vars->player->dist_proj_plane = (vars->map->width / 2) / (tan(FOV / 2));
	while (i < vars->map->num_rays)
	{
		vars->ray[i]->ray_angle = vars->player->rotation_angle +
			atan2(i - vars->map->num_rays / 2, vars->player->dist_proj_plane);
		vars->ray[i]->ray_angle = ft_normalize_angle(vars->ray[i]->ray_angle);
		check_closest_wall(vars, vars->ray[i], vars->ray[i]->ray_angle);
		i++;
	}
	return (0);
}

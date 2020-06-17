/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 00:19:46 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/15 02:49:48 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_ray(t_ray *ray, t_point *collision, double dist_wall, int coord)
{
	ray->collision = collision;
	ray->dist_wall = dist_wall;
	ray->coord = coord;
}

void	check_closest_wall(t_vars *vars, t_ray *ray, double ray_angle)
{
	t_point	*horz_intercept;
	t_point *vert_intercept;
	double	dist_horz;
	double	dist_vert;

	horz_intercept = cast_ray(vars, ray_angle, HORZ, create_point(0, 0, 0));
	vert_intercept = cast_ray(vars, ray_angle, VERT, create_point(0, 0, 0));
	dist_horz = is_end_window(vars->map, horz_intercept->x, horz_intercept->y) ?
	INT_MAX : dist_btw_points(vars->player->posit->x, vars->player->posit->y,
	horz_intercept->x, horz_intercept->y);
	dist_vert = is_end_window(vars->map, vert_intercept->x, vert_intercept->y) ?
	INT_MAX : dist_btw_points(vars->player->posit->x, vars->player->posit->y,
	vert_intercept->x, vert_intercept->y);
	ray->ray_angle = ray_angle;
	if (dist_horz < dist_vert)
	{
		assign_ray(ray, horz_intercept, dist_horz, HORZ);
		free(vert_intercept);
	}
	else
	{
		assign_ray(ray, vert_intercept, dist_vert, VERT);
		free(horz_intercept);
	}
}

t_ray	**ft_raycast(t_vars *vars)
{
	t_ray	**ray;
	double	ray_angle;
	int		i;

	ray = ft_calloc(vars->map->num_rays, sizeof(t_ray *));
	ray_angle = vars->player->rotation_angle - (FOV / 2);
	i = 0;
	while (i < vars->map->num_rays)
	{
		ray_angle = ft_normalize_angle(ray_angle);
		ray[i] = ft_calloc(1, sizeof(t_ray));
		check_closest_wall(vars, ray[i], ray_angle);
		ray_angle += FOV / vars->map->num_rays;
		i++;
	}
	return (ray);
}

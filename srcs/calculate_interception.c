/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_interception.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 01:53:57 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/06 00:55:54 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	*horz_interception(t_vars *vars, t_point *intercept, float ray_angle)
{
	t_point	*step;

	step = create_point(0, 0, 0);
	intercept->y = floor(vars->player->posit->y / vars->map->tile_y) * vars->map->tile_y;
	intercept->y += ray_facing(ray_angle, ray_down) ? vars->map->tile_y : 0;
	intercept->x = vars->player->posit->x + (intercept->y - vars->player->posit->y) / tan(ray_angle);
	step->y = vars->map->tile_y;
	step->y *= ray_facing(ray_angle, ray_up) ? -1 : 1;
	step->x = vars->map->tile_y / tan(ray_angle);
	step->x *= (ray_facing(ray_angle, ray_left) && step->x > 0) ? -1 : 1;
	step->x *= (ray_facing(ray_angle, ray_right) && step->x < 0) ? -1 : 1;
	return (step);
}

t_point	*vert_interception(t_vars *vars, t_point *intercept, float ray_angle)
{
	t_point	*step;

	step = create_point(0, 0, 0);
	if (ray_angle == PI / 2  || ray_angle == 3 * PI / 2)
		return (NULL);
	intercept->x = floor(vars->player->posit->x / vars->map->tile_x) * vars->map->tile_x;
	intercept->x += ray_facing(ray_angle, ray_right) ? vars->map->tile_x : 0;
	intercept->y = vars->player->posit->y + (intercept->x - vars->player->posit->x) * tan(ray_angle);
	step->x = vars->map->tile_x;
	step->x *= ray_facing(ray_angle, ray_left) ? -1 : 1;
	step->y = vars->map->tile_x * tan(ray_angle);
	step->y *= (ray_facing(ray_angle, ray_up) && step->y > 0) ? -1 : 1;
	step->y *= (ray_facing(ray_angle, ray_down) && step->y < 0) ? -1 : 1;
	return (step);
}

t_point	*cast_ray(t_vars *vars, float ray_angle, int coord)
{
	t_point	*step;
	t_point *next;
	float	x_check;
	float	y_check;

	next = create_point(0, 0, 0);
	step = (coord == HORZ) ? horz_interception(vars, next, ray_angle) :
							vert_interception(vars, next, ray_angle);
	while (!is_end_window(vars->map, next->x, next->y))
	{
		x_check = next->x + ((ray_facing(ray_angle, ray_left) && coord == VERT) ? -1 : 0);
		x_check += ((ray_facing(ray_angle, ray_right) && coord == VERT) ? 1 : 0);
		y_check = next->y + ((ray_facing(ray_angle, ray_down) && coord == HORZ) ? 1 : 0);
		y_check += ((ray_facing(ray_angle, ray_up) && coord == HORZ) ? -1 : 0);
		if (is_wall(vars->map, x_check, y_check))
			break ;
		else
		{
			next->x += step->x;
			next->y += step->y;
		}
	}
	free(step);
	return (next);
}

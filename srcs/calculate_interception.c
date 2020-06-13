/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_interception.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 01:53:57 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/13 03:32:37 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	*horz_inter(t_vars *vars, t_point *intercept, float ray_angle)
{
	t_point	*step;

	step = create_point(0, 0, 0);
	intercept->y = floor(vars->player->posit->y / TILE_SIZE) * TILE_SIZE;
	intercept->y += ray_facing(ray_angle, ray_down) ? TILE_SIZE : 0;
	intercept->x = vars->player->posit->x + (intercept->y - vars->player->
					posit->y) / tan(ray_angle);
	step->y = TILE_SIZE;
	step->y *= ray_facing(ray_angle, ray_up) ? -1 : 1;
	step->x = TILE_SIZE / tan(ray_angle);
	step->x *= (ray_facing(ray_angle, ray_left) && step->x > 0) ? -1 : 1;
	step->x *= (ray_facing(ray_angle, ray_right) && step->x < 0) ? -1 : 1;
	return (step);
}

t_point	*vert_inter(t_vars *vars, t_point *intercept, float ray_angle)
{
	t_point	*step;

	step = create_point(0, 0, 0);
	intercept->x = floor(vars->player->posit->x / TILE_SIZE) * TILE_SIZE;
	intercept->x += ray_facing(ray_angle, ray_right) ? TILE_SIZE : 0;
	intercept->y = vars->player->posit->y + (intercept->x - vars->player->
					posit->x) * tan(ray_angle);
	step->x = TILE_SIZE;
	step->x *= ray_facing(ray_angle, ray_left) ? -1 : 1;
	step->y = TILE_SIZE * tan(ray_angle);
	step->y *= (ray_facing(ray_angle, ray_up) && step->y > 0) ? -1 : 1;
	step->y *= (ray_facing(ray_angle, ray_down) && step->y < 0) ? -1 : 1;
	return (step);
}

t_point	*cast_ray(t_vars *vars, float ray_angle, int coord, t_point *next)
{
	t_point	*step;
	float	x_chk;
	float	y_chk;

	step = (coord == HORZ) ? horz_inter(vars, next, ray_angle) :
							vert_inter(vars, next, ray_angle);
	while (!is_end_window(vars->map, next->x, next->y))
	{
		x_chk = next->x + ((ray_facing(ray_angle, ray_left) && coord == VERT) ?
					-1 : 0);
		x_chk += ((ray_facing(ray_angle, ray_right) && coord == VERT) ? 1 : 0);
		y_chk = next->y + ((ray_facing(ray_angle, ray_down) && coord == HORZ) ?
				1 : 0);
		y_chk += ((ray_facing(ray_angle, ray_up) && coord == HORZ) ? -1 : 0);
		if (is_wall(vars->map, x_chk, y_chk, '1'))
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

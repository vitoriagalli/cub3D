/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_intercept.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 01:53:57 by vscabell          #+#    #+#             */
/*   Updated: 2020/07/24 21:15:14 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ray_facing(double angle, int way)
{
	int	up;
	int	down;
	int	left;
	int	right;

	down = (angle > 0 && angle < PI) ? TRUE : FALSE;
	up = !(down) ? TRUE : FALSE;
	left = (angle > PI / 2 && angle < 3 * PI / 2) ? TRUE : FALSE;
	right = !left ? TRUE : FALSE;
	if (way == ray_up)
		return (up);
	else if (way == ray_down)
		return (down);
	else if (way == ray_left)
		return (left);
	else if (way == ray_right)
		return (right);
	return (-1);
}

static void	horz_inter(t_vars *vars, t_point *intercept, double ray_angle,
						t_point *step)
{
	intercept->y = floor(vars->player->posit->y / TILE_SIZE) * TILE_SIZE;
	intercept->y += ray_facing(ray_angle, ray_down) ? TILE_SIZE : 0;
	intercept->x = vars->player->posit->x + (intercept->y - vars->player->
					posit->y) / tan(ray_angle);
	step->y = TILE_SIZE;
	step->y *= ray_facing(ray_angle, ray_up) ? -1 : 1;
	step->x = TILE_SIZE / tan(ray_angle);
	step->x *= (ray_facing(ray_angle, ray_left) && step->x > 0) ? -1 : 1;
	step->x *= (ray_facing(ray_angle, ray_right) && step->x < 0) ? -1 : 1;
}

static void	vert_inter(t_vars *vars, t_point *intercept, double ray_angle,
						t_point *step)
{
	intercept->x = floor(vars->player->posit->x / TILE_SIZE) * TILE_SIZE;
	intercept->x += ray_facing(ray_angle, ray_right) ? TILE_SIZE : 0;
	intercept->y = vars->player->posit->y + (intercept->x - vars->player->
					posit->x) * tan(ray_angle);
	step->x = TILE_SIZE;
	step->x *= ray_facing(ray_angle, ray_left) ? -1 : 1;
	step->y = TILE_SIZE * tan(ray_angle);
	step->y *= (ray_facing(ray_angle, ray_up) && step->y > 0) ? -1 : 1;
	step->y *= (ray_facing(ray_angle, ray_down) && step->y < 0) ? -1 : 1;
}

void		cast_ray(t_vars *vars, double ray_angle, int coord,
							t_point *next)
{
	t_point	step;
	double	x_chk;
	double	y_chk;

	(coord == HORZ) ?
		horz_inter(vars, next, ray_angle, &step) :
		vert_inter(vars, next, ray_angle, &step);
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
			next->x += step.x;
			next->y += step.y;
		}
	}
}

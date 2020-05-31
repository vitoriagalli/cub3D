/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:20 by vscabell          #+#    #+#             */
/*   Updated: 2020/05/31 07:52:09 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_fov(t_vars *vars)
{
	float	ray_angle;
	int x1; int y1;
	int 	i;

	ray_angle = vars->player->rotation_angle - FOV / 2;
	i = 0;
	while(i < vars->map->num_rays)
	{
		x1 = vars->player->x + cos(ray_angle) * 100;
		y1 = vars->player->y + sin(ray_angle) * 100;
		ft_line(vars->data, vars->player->x, vars->player->y, x1, y1, 0xff00ff00);
		ray_angle += FOV / vars->map->num_rays;
		i++;
	}
}

float	*calculate_rays(t_vars *vars)
{
	float	ray_angle;
	t_point	*intercept;
	float	*ray;
	//int		column_id;
	int 	i;

	ray = alocate_memory(sizeof(float) * vars->map->num_rays);
	ray_angle = vars->player->rotation_angle - (FOV / 2);
	i = 0;
	while(i < vars->map->num_rays)
	{
		ray_angle = ft_normalize_angle(ray_angle);
		intercept = closest_wall(vars, ray_angle);
		ray[i] = dist_btw_points(vars->player->x, vars->player->y, intercept->x, intercept->y);
		ft_line(vars->data, vars->player->x * MAP2D_SCALE,
		vars->player->y * MAP2D_SCALE,
		intercept->x * MAP2D_SCALE,
		intercept->y * MAP2D_SCALE, intercept->color);
		ray_angle += FOV / vars->map->num_rays;
		free(intercept);
		i++;
	}
	return(ray);
}

//	0 -> HORIZONTAL				1 -> VERTICAL
t_point	*cast_ray(t_vars *vars, float ray_angle, int coord)
{
	t_point	*step;
	t_point *intercept;
	float	next_x;
	float	next_y;
	float	x_check;
	float	y_check;

	intercept = create_point(0, 0, 0xFF00FF00);
	step = coord == 0 ?
		horiz_inters(vars, intercept, ray_angle) :
		vert_inters(vars, intercept, ray_angle);
	next_x = intercept->x;
	next_y = intercept->y;
	while (!is_end_window(vars->map, next_x, next_y))
	{
		x_check = next_x + ((ray_facing(ray_angle, ray_left) && coord == 1) ? -1 : 0);
		x_check += ((ray_facing(ray_angle, ray_right) && coord == 1) ? 1 : 0);
		y_check = next_y + ((ray_facing(ray_angle, ray_down) && coord == 0) ? 1 : 0);
		y_check += ((ray_facing(ray_angle, ray_up) && coord == 0) ? -1 : 0);

		if (is_wall(vars->map, x_check, y_check))
		{
			assign_point(intercept, next_x, next_y, intercept->color);
			free(step);
			return (intercept);
		}
		else
		{
			next_x += step->x;
			next_y += step->y;
		}
	}
	free(step);
	assign_point(intercept, 0, 0, 0);
	return(intercept);  //NÃO ACHOU WALL, RETORNAR VAR VALUE
}


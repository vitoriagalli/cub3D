/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:20 by vscabell          #+#    #+#             */
/*   Updated: 2020/05/31 02:54:12 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_fov(t_vars *vars)
{
	float	ray_angle;
	int x1; int y1;
	//int		column_id;
	int 	i;

	//column_id = 0;
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

	//column_id = 0;

	ray = alocate_memory(sizeof(float) * vars->map->num_rays);

	ray_angle = ft_normalize_angle(vars->player->rotation_angle - FOV / 2);
	i = 0;
	while(i < vars->map->num_rays)
	{
		intercept = closest_wall(vars, ray_angle);
		ray[i] = dist_btw_points(vars->player->x, vars->player->y, intercept->x, intercept->y);

		//printf("angle = %f   distance = %f\n", ray_angle,
		//dist_btw_points(player->x, player->y, intercept->x, intercept->y));

		ft_line(vars->data, vars->player->x * MAP2D_SCALE,
		vars->player->y * MAP2D_SCALE,
		intercept->x * MAP2D_SCALE,
		intercept->y * MAP2D_SCALE, intercept->color);

		ray_angle += FOV / vars->map->num_rays;
		ray_angle = ft_normalize_angle(ray_angle);
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
	int		next_x;
	int		next_y;
	int		x_check;
	int		y_check;

	intercept = create_point(0, 0, 0xFF00FF00);
	step = coord == 0 ?
		horiz_inters(vars, intercept, ray_angle) :
		vert_inters(vars, intercept, ray_angle);
	next_x = intercept->x;
	next_y = intercept->y;
	while (!is_end_window(vars->map, next_x, next_y))
	{
		//x_check = next_x + ((ray_facing(ray_angle, ray_left) && coord == 1) ? -1 : 0);
		//x_check += ((ray_facing(ray_angle, ray_right) && coord == 1) ? 1 : 0);
		//y_check = next_y + ((ray_facing(ray_angle, ray_down) && coord == 0) ? 1 : 0);
		//y_check += ((ray_facing(ray_angle, ray_up) && coord == 0) ? -1 : 0);

		x_check = next_x;
		y_check = next_y;

		if (ray_facing(ray_angle, ray_right))
			x_check += 2;
		else
			x_check -= 2;
		if (ray_facing(ray_angle, ray_down))
			y_check += 2;
		else
			y_check -= 2;


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


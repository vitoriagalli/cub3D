/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 02:57:12 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/13 16:51:03 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_3dmap(t_vars *vars)
{
	float	correct_dist_plane;
	float	wall_proj_height;
	int		i;

	i = 0;
	vars->player->dist_proj_plane = (vars->map->width / 2) / (tan(FOV / 2));
	while (i < vars->map->num_rays)
	{
		correct_dist_plane = vars->ray[i]->dist_wall *
					cos(vars->ray[i]->ray_angle - vars->player->rotation_angle);
		wall_proj_height = TILE_SIZE / correct_dist_plane *
							vars->player->dist_proj_plane;
		wall_proj_height = (wall_proj_height < vars->map->height) ?
							wall_proj_height : vars->map->height;
		store_all_colors(vars, wall_proj_height, i);
		i++;
	}
}

void	store_all_colors(t_vars *vars, float wall_proj_height, int i)
{
	float	limit_y[2];
	int		x;
	int		y;

	limit_y[0] = (vars->map->height / 2) - (wall_proj_height / 2);
	limit_y[1] = (vars->map->height / 2) + (wall_proj_height / 2);
	x = i * WALL_WIDTH;
	while (x < (i + 1) * WALL_WIDTH)
	{
		y = -1;
		while (++y <= limit_y[0] && y < vars->map->height)
			my_mlx_pixel_put(vars->data, x, y, vars->map->color->ceilling);
		y--;
		while (++y <= limit_y[1] && y < vars->map->height)
			my_mlx_pixel_put(vars->data, x, y, store_tex(vars, y, i, limit_y));
		y--;
		while (++y <= vars->map->height)
			my_mlx_pixel_put(vars->data, x, y, vars->map->color->floor);
		x++;
	}
}

int		store_tex(t_vars *vars, int y, int i, float *limit)
{
	t_ray	*ray;
	float	ymin;
	float	ymax;

	ray = NULL;
	ymin = limit[0];
	ymax = limit[1];
	ray = vars->ray[i];
	if (ray_facing(ray->ray_angle, ray_up) && ray->coord == HORZ)
		return (get_texture_color(vars->tex[north],
				(int)ray->collision->x % vars->tex[north]->width,
				(y - ymin) * (vars->tex[north]->height) / (ymax - ymin)));
	else if (ray_facing(ray->ray_angle, ray_down) && ray->coord == HORZ)
		return (get_texture_color(vars->tex[south],
				(int)ray->collision->x % vars->tex[north]->width,
				(y - ymin) * (vars->tex[south]->height) / (ymax - ymin)));
	else if (ray_facing(ray->ray_angle, ray_right) && ray->coord == VERT)
		return (get_texture_color(vars->tex[east],
				(int)ray->collision->y % vars->tex[north]->width,
				(y - ymin) * (vars->tex[east]->height) / (ymax - ymin)));
	else if (ray_facing(ray->ray_angle, ray_left) && ray->coord == VERT)
		return (get_texture_color(vars->tex[west],
				(int)ray->collision->y % vars->tex[north]->width,
				(y - ymin) * (vars->tex[west]->height) / (ymax - ymin)));
		return (0);
}

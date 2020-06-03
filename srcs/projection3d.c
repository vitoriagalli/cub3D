/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 02:57:12 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/03 22:09:36 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		put_player_3dmap(t_vars *vars)
{
	int **pixels_buffer;

	pixels_buffer = alocate_buffer(vars->map->height, vars->map->width);
	pixels_buffer = get_pixel_info(vars, pixels_buffer);
	project_game(vars, pixels_buffer);
	clean_buffer(pixels_buffer, vars->map->height);
}

int		**get_pixel_info(t_vars *vars, int **buffer)
{
	float	correct_dist_plane;
	float	dist_proj_plane;
	float	wall_proj_height;
	int		i;

	i = 0;
	dist_proj_plane = (vars->map->width / 2) / (tan(FOV / 2));
	while (i < vars->map->num_rays)
	{
		correct_dist_plane = vars->ray[i]->dist_wall * cos(vars->ray[i]->ray_angle - vars->player->rotation_angle);
		wall_proj_height = (vars->map->tile_size / correct_dist_plane) * dist_proj_plane;
		wall_proj_height = (wall_proj_height < vars->map->height) ? wall_proj_height : vars->map->height;
		store_all_colors(vars, buffer, wall_proj_height, i);
		i++;
	}
	return (buffer);
}

void	store_all_colors(t_vars *vars, int **buffer, float wall_proj_height, int i)
{
	float	limit[2];
	int 	x;
	int 	y;

	limit[0] = (vars->map->height / 2) - (wall_proj_height / 2);
	limit[1] = (vars->map->height / 2) + (wall_proj_height / 2);
	x = i * WALL_WIDTH;
	while (x < (i + 1) * WALL_WIDTH)
	{
		y = -1;
		while (++y < limit[0] && y < vars->map->height)
			buffer[y][x] = vars->map->color->ceilling;
		while (++y < limit[1] && y < vars->map->height)
			buffer[y][x] = store_texture(vars, y, i, limit);
		while (++y < vars->map->height)
			buffer[y][x] = vars->map->color->floor;
		x++;
	}
}

void	project_game(t_vars *vars, int **color_buf)
{
	int x;
	int y;

	x = 0;
	while(x < vars->map->width)
	{
		y = 0;
		while(y < vars->map->height)
		{
			my_mlx_pixel_put(vars->data, x, y, color_buf[y][x]);
			y++;
		}
		x++;
	}
}

void	clean_structure(t_vars *vars)
{
	int i;

	i = 0;
	while (i < vars->map->num_rays)
	{
		free(vars->ray[i]->collision);
		vars->ray[i]->collision = NULL;
		free(vars->ray[i]);
		vars->ray[i] = NULL;
		i++;
	}
	free(vars->ray);
	vars->ray = NULL;
}

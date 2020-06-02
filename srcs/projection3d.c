/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 02:57:12 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/02 21:17:49 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void		put_player_3dmap(t_vars *vars)
{
	int **pixels_buffer;

	pixels_buffer = alocate_buffer(vars->map->height, vars->map->width);
	pixels_buffer = store_pixel_info(vars, pixels_buffer);
	project_game(vars, pixels_buffer);
	clean_buffer(pixels_buffer, vars->map->height);
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



// void	project_things(t_vars *vars, float wall_proj_height, int i)
// {
// 	t_point	*thing;
// 	int		color;
// 	float	ceilling_lim;
// 	float	wall_lim;
// 	int 	x;
// 	int 	y;

// 	thing = create_point(0, 0, 0);
// 	ceilling_lim = (vars->map->height / 2) - (wall_proj_height / 2);
// 	wall_lim = (vars->map->height / 2) + (wall_proj_height / 2);
// 	x = i * WALL_WIDTH;
// 	while (x < (i + 1) * WALL_WIDTH)
// 	{
// 		y = 0;
// 		while (y < vars->map->height)
// 		{
// 			if (y > 0 && y < ceilling_lim)
// 				color = vars->map->color->ceilling;
// 			else if (y >= ceilling_lim && y < wall_lim)
// 				color = get_color(vars, i, y);
// 			else
// 			 	color = vars->map->color->floor;
// 			my_mlx_pixel_put(vars->data, x, y, color);
// 			y++;
// 		}
// 		x++;
// 	}
// 	free(thing);
// }

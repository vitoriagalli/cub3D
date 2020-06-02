/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 16:26:11 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/02 22:04:07 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	store_things(t_vars *vars, int **buffer, float wall_proj_height, int i)
{
	t_point	*thing;
	float	ceilling_lim;
	float	wall_lim;
	int 	x;
	int 	y;

	thing = create_point(0, 0, 0);
	ceilling_lim = (vars->map->height / 2) - (wall_proj_height / 2);
	wall_lim = (vars->map->height / 2) + (wall_proj_height / 2);
	x = i * WALL_WIDTH;
	while (x < (i + 1) * WALL_WIDTH)
	{
		y = 0;
		while (y < vars->map->height)
		{
			while (y < ceilling_lim)
			{
				buffer[y][x] = vars->map->color->ceilling;
				y++;
			}
			while (y < wall_lim)
			{
				buffer[y][x] = get_color(vars, i, x);
				y++;
			}
			while (y < vars->map->height)
			{
				buffer[y][x] = vars->map->color->floor;
				y++;
			}
		}
		x++;
	}
	free(thing);
}

int		**store_pixel_info(t_vars *vars, int **buffer)
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
		store_things(vars, buffer, wall_proj_height, i);
		i++;
	}
	return (buffer);
}


int		get_color(t_vars *vars, int n_ray, int column)
{
	t_ray	*ray = NULL;
	t_color	*color = NULL;

	ray = vars->ray[n_ray]; 			(void) column;
	color = vars->map->color;
	if (ray_facing(ray->ray_angle, ray_up) && ray->coord == HORZ)
		return (color->north_text);
	else if (ray_facing(ray->ray_angle, ray_down) && ray->coord == HORZ)
		return (color->south_text);
	else if (ray_facing(ray->ray_angle, ray_right) && ray->coord == VERT)
		return (color->east_text);
	else if (ray_facing(ray->ray_angle, ray_left) && ray->coord == VERT)
		return (color->west_text);
		// return (get_texture(vars, n_ray, column));

	else
		return (-1);
}





int ft_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	shade_wall(float dist, int r, int g, int b)
{
	int		delta;
	int		delta_max;
	float	dist_max;

	dist_max = 1100;
	delta_max = 240;
	delta = dist * delta_max / dist_max;
	r -= r > delta? delta : 0;
	g -= g > delta? delta : 0;
	b -= b > delta? delta : 0;
	return (ft_rgb(r, g, b));
}

unsigned int rgb(double ratio)
{
    //we want to normalize ratio so that it fits in to 6 regions
    //where each region is 256 units long

    int normalized = (int)(ratio * 256 * 6);

    //find the distance to the start of the closest region
    int x = normalized % 256;

    int red = 0, grn = 0, blu = 0;
    switch(normalized / 256)
    {
    	case 0: red = 255;      grn = x;        blu = 0;       break;//red
    	case 1: red = 255 - x;  grn = 255;      blu = 0;       break;//yellow
    	case 2: red = 0;        grn = 255;      blu = x;       break;//green
    	case 3: red = 0;        grn = 255 - x;  blu = 255;     break;//cyan
    	case 4: red = x;        grn = 0;        blu = 255;     break;//blue
    	case 5: red = 255;      grn = 0;        blu = 255 - x; break;//magenta
    }

    return red + (grn << 8) + (blu << 16);
}

unsigned int	ft_color(int i)
{
	double range = 500;
	unsigned int color;

	i = i % (int)range;
	color = rgb(i / range);

	return (color);
}


// int		*get_column_colors(t_vars *vars, float wall_proj_height, int i)
// {
// 	int		*column_buffer = NULL;					// i = num da coluna
// 	float	ceilling_lim;
// 	float	wall_lim;
// 	int 	x;
// 	int 	y;

// 	ceilling_lim = (vars->map->height / 2) - (wall_proj_height / 2);
// 	wall_lim = (vars->map->height / 2) + (wall_proj_height / 2);
// 	x = i * WALL_WIDTH;
// 	while (x < (i + 1) * WALL_WIDTH)
// 	{
// 		y = 0;
// 		while (y < vars->map->height)
// 		{
// 			while (y < ceilling_lim)
// 			{
// 				column_buffer[y][x] = vars->map->color->ceilling;
// 				y++;
// 			}
// 			while(y >= ceilling_lim && y < wall_lim)
// 			{
// 				column_buffer[y][x] = *ft_rgb(100, 100, 100);
// 				// buffer_colors[y][x] = get_color(vars, i, y);
// 				y++;
// 			}
// 			while (y < vars->map->height)
// 			{
// 			 	column_buffer[y][x] = vars->map->color->floor;
// 				y++;
// 			}

// 			y++;
// 		}
// 		x++;
// 	}
// 	return (column_buffer);
// }

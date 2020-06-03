/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 16:26:11 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/03 18:54:49 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		store_texture(t_vars *vars, int y, int i, float *limit)
{
	t_ray	*ray = NULL;
	t_color	*color = NULL;

	float ymin = limit[0];
	float ymax = limit[1];

	int offset;
	int	ytext;

	offset = (int)vars->ray[i]->collision->x % vars->map->tile_size;
	ytext = (y - ymin) * (vars->tex->height - 0) / (ymax - ymin) + 0;

	ray = vars->ray[i];
	color = vars->map->color;

	if (ray_facing(ray->ray_angle, ray_up) && ray->coord == HORZ)
		// return (color->north_text);
		return (get_texture_color(vars->tex, offset, ytext));
	else if (ray_facing(ray->ray_angle, ray_down) && ray->coord == HORZ)
		return (color->south_text);
	else if (ray_facing(ray->ray_angle, ray_right) && ray->coord == VERT)
		return (color->east_text);
	else if (ray_facing(ray->ray_angle, ray_left) && ray->coord == VERT)
		return (color->west_text);

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

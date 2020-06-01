/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 16:26:11 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/01 21:46:10 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int		get_color(t_ray *ray, t_color *color)
{
	if (ray_facing(ray->ray_angle, ray_up) && ray->coord == HORZ)
		return (color->north_text);
	else if (ray_facing(ray->ray_angle, ray_down) && ray->coord == HORZ)
		return (color->south_text);
	else if (ray_facing(ray->ray_angle, ray_right) && ray->coord == VERT)
		return (color->east_text);
	else if (ray_facing(ray->ray_angle, ray_left) && ray->coord == VERT)
		return (color->west_text);
	else
		return (-1);
}

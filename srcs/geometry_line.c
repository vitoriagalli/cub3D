/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 03:11:15 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/14 23:08:27 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	loop_ray_x(t_data *img, int *p1, int *dif, t_point coord)
{
	int	d;

	d = dif[VERT] - dif[HORZ];
	while (coord.x <= p1[HORZ])
	{
		if (d < 0)
			d += dif[2];
		else
		{
			d += dif[3];
			coord.y += (coord.y < p1[VERT]) ? 1 : -1;
		}
		coord.x++;
		my_mlx_pixel_put(img, coord.x, coord.y, dif[4]);
	}
}

static void	ft_increment_x(t_data *img, int *p0, int *p1, int *dif)
{
	t_point	coord;

	if (p0[HORZ] < p1[HORZ])
	{
		coord.x = p0[HORZ];
		coord.y = p0[VERT];
	}
	else
	{
		ft_swap(&p0[HORZ], &p1[HORZ]);
		ft_swap(&p0[VERT], &p1[VERT]);
		coord.x = p0[HORZ];
		coord.y = p0[VERT];
	}
	loop_ray_x(img, p1, dif, coord);
}

static void	loop_ray_y(t_data *img, int *p1, int *dif, t_point coord)
{
	int	d;

	d = dif[HORZ] - dif[VERT];
	while (coord.y <= p1[VERT])
	{
		if (d < 0)
			d += dif[2];
		else
		{
			d += dif[3];
			coord.x += (coord.x < p1[HORZ]) ? 1 : -1;
		}
		coord.y++;
		my_mlx_pixel_put(img, coord.x, coord.y, dif[4]);
	}
}

static void	ft_increment_y(t_data *img, int *p0, int *p1, int *dif)
{
	t_point	coord;

	if (p0[VERT] < p1[VERT])
	{
		coord.x = p0[HORZ];
		coord.y = p0[VERT];
	}
	else
	{
		ft_swap(&p0[HORZ], &p1[HORZ]);
		ft_swap(&p0[VERT], &p1[VERT]);
		coord.x = p0[HORZ];
		coord.y = p0[VERT];
	}
	loop_ray_y(img, p1, dif, coord);
}

void		ft_line(t_data *img, int *p0, int *p1, int color)
{
	int	dif[5];

	dif[4] = color;
	dif[HORZ] = (p1[HORZ] - p0[HORZ]);
	dif[HORZ] *= (dif[HORZ] > 0) ? 1 : -1;
	dif[VERT] = (p1[VERT] - p0[VERT]);
	dif[VERT] *= (dif[VERT] > 0) ? 1 : -1;
	if (dif[HORZ] >= dif[VERT])
	{
		dif[2] = dif[VERT];
		dif[3] = dif[VERT] - dif[HORZ];
		ft_increment_x(img, p0, p1, dif);
	}
	else
	{
		dif[2] = dif[HORZ];
		dif[3] = dif[HORZ] - dif[VERT];
		ft_increment_y(img, p0, p1, dif);
	}
}

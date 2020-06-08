/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 03:11:15 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/06 21:38:46 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_rectangle(t_data *img, t_point point, int l_width, int l_height)
{
	int x;
	int y;

	x = 0;
	while (x < l_width)
	{
		y = 0;
		while (y < l_height)
		{
			my_mlx_pixel_put(img, point.x + x, point.y + y, point.color);
			y++;
		}
		x++;
	}
}

void	ft_increment_x(t_data *img, int *p0, int *p1, int *dif)
{
	int x;
	int	y;
	int d;

	d = dif[VERT] - dif[HORZ];
	if (p0[HORZ] < p1[HORZ])
	{
		x = p0[HORZ];
		y = p0[VERT];
	}
	else
	{
		ft_swap(&p0[HORZ], &p1[HORZ]);
		ft_swap(&p0[VERT], &p1[VERT]);
		x = p0[HORZ];
		y = p0[VERT];
	}
	while(x <= p1[HORZ])
	{
		if (d < 0)
			d += dif[2];
		else
		{
			d += dif[3];
			y += (y < p1[VERT]) ? 1 : -1;
		}
		x++;
		my_mlx_pixel_put(img, x, y, dif[4]);
	}
}

void	ft_increment_y(t_data *img, int *p0, int *p1, int *dif)
{
	int x;
	int y;
	int d;

	d = dif[HORZ] - dif[VERT];
	if (p0[VERT] < p1[VERT])
	{
		x = p0[HORZ];
		y = p0[VERT];
	}
	else
	{
		ft_swap(&p0[HORZ], &p1[HORZ]);
		ft_swap(&p0[VERT], &p1[VERT]);
		x = p0[HORZ];
		y = p0[VERT];
	}
	while(y <= p1[VERT])
	{
		if (d < 0)
			d += dif[2];
		else
		{
			d += dif[3];
			x += (x < p1[HORZ]) ? 1 : -1;
		}
		y++;
		my_mlx_pixel_put(img, x, y, dif[4]);
	}
}

void	ft_line(t_data *img, int *p0, int *p1, int color)
{
	int	dif[5];

	dif[4] = color;
	dif[HORZ] = (p1[HORZ] - p0[HORZ]);
	dif[HORZ] *= (dif[HORZ] > 0) ? 1 : -1;
	dif[VERT] = (p1[VERT] - p0[VERT]);
	dif[VERT] *= (dif[VERT] > 0) ? 1 : -1;
	if (dif[HORZ] >= dif[VERT])
	{
		dif[2] = dif[VERT]; 					//	ds = dy
		dif[3] = dif[VERT] - dif[HORZ];			//  dt = dy - dx
		ft_increment_x(img, p0, p1, dif);
	}
	else
	{
		dif[2] = dif[HORZ];						//	ds = dx
		dif[3] = dif[HORZ] - dif[VERT];			//  dt = dx - dy
		ft_increment_y(img, p0, p1, dif);
	}
}

static void	ft_put_symmetry(t_data *img, int *center, int *p, int color)
{
	int xc;
	int yc;
	int x;
	int yl;

	xc = center[HORZ];
	yc = center[VERT];
	x = p[HORZ];
	yl = p[VERT];
	while (yl >= 0)
	{
		my_mlx_pixel_put(img, x + xc, yl + yc, color);
		my_mlx_pixel_put(img, yl + xc, -x + yc, color);
		my_mlx_pixel_put(img, x + xc, -yl + yc, color);
		my_mlx_pixel_put(img, yl + xc, x + yc, color);
		my_mlx_pixel_put(img, -x + xc, yl + yc, color);
		my_mlx_pixel_put(img, -yl + xc, -x + yc, color);
		my_mlx_pixel_put(img, -x + xc, -yl + yc, color);
		my_mlx_pixel_put(img, -yl + xc, x + yc, color);
		yl--;
	}
}

void	ft_circle(t_data *img, int *center, int radius, int color)
{
	int p[2];
	int h;

	h = 1 - radius;
	p[HORZ] = 0;
	p[VERT] = radius;
	while (p[VERT] > p[HORZ])
	{
		if (h < 0)
			h = h + 2 * p[HORZ] + 3;
		else
		{
			h = h + 2 * (p[HORZ] - p[VERT]) + 5;
			p[VERT]--;
		}
		ft_put_symmetry(img, center, p, color);
		p[HORZ]++;
	}
}

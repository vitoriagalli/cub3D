/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 03:11:15 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/01 03:33:20 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_rectangle(t_data *img, t_point point, int l_width, int l_height)
{
	int x = 0;
	int y = 0;

	while(x < l_width)
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


void	ft_increment_x(t_data *img, int x0, int y0, int x1, int y1, int dx, int dy, int color)
{
	int x, y;
	int d = dy - dx;
	int ds = dy;
	int dt = dy - dx;

	if (x0 < x1)
	{
		x = x0;
		y = y0;
	}
	else
	{
		x = x1;
		y = y1;
		x1 = x0;
		y1 = y0;
		x0 = x;
		y0 = y;
	}
	while(x <= x1)
	{
		if (d<0)
			d = d + ds;
		else
		{
			d = d + dt;
			if (y < y1)
				y++;
			else
				y--;
		}
		x++;
		my_mlx_pixel_put(img, x, y, color);
	}
}

void	ft_increment_y(t_data *img, int x0, int y0, int x1, int y1, int dx, int dy, int color)
{
	int x, y;
	int d = dx - dy;
	int ds = dx;
	int dt = dx - dy;

	if (y0 < y1)
	{
		x = x0;
		y = y0;
	}
	else
	{
		x = x1;
		y = y1;
		x1 = x0;
		y1 = y0;
		x0 = x;
		y0 = y;
	}
	while(y <= y1)
	{
		if (d<0)
			d = d + ds;
		else
		{
			d = d + dt;
			if (x < x1)
				x++;
			else
				x--;
		}
		y++;
		my_mlx_pixel_put(img, x, y, color);
	}
}

void ft_line(t_data *img, int x0, int y0, int x1, int y1, int color)
{
	int 	dx;
	int 	dy;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);

	if(dx >= dy)
		ft_increment_x(img, x0, y0, x1, y1, dx, dy, color);
	else
	{
		/*
		** slope > 45°
		** o incremento é sobre y e não sobre x
		*/
		ft_increment_y(img, x0, y0, x1, y1, dx, dy, color);
	}
}




void ft_line_f(t_data *img, int x0, int y0, int x1, int y1, int color)
{
	int 	dx;
	int 	dy;
	int		x = x0;
	int		y = y0;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);

	if(dx >= dy)		//slope < 45°
	{
		while (x < x1)
		{
			x = x + 1;
			y = y + dy/dx;
			my_mlx_pixel_put(img, x, y, color);
		}
	}
	else				//slope > 45°
	{
		while (x < x1)
		{
			x = x + dx/dy;
			y = y + 1;
			my_mlx_pixel_put(img, x, y, color);
		}

	}
}

/*
** ft_circle function use float as variable
*/

// void	ft_arc_circle(t_data *img, t_player *center)
// {
// 	float angle;
// 	float increase_angle = 0.01;
// 	int new_x;
// 	int new_y;

// 	angle = 0.0;
// 	while (angle < 2 * M_PI)
// 	{
// 		new_x = center->x + (center->radius * cos(angle));
// 		new_y = center->y + (center->radius * sin(angle));
// 		my_mlx_pixel_put(img, new_x, new_y, center->color);
// 		angle += increase_angle;
// 	}
// }


void	ft_put_symmetry(t_data *img,  int xc, int yc, int x, int y, int color, int fill)
{
	if (fill == 1)
	{
		int yl = y;
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
	else
	{
		my_mlx_pixel_put(img, x + xc, y + yc, color);
		my_mlx_pixel_put(img, y + xc, -x + yc, color);
		my_mlx_pixel_put(img, x + xc, -y + yc, color);
		my_mlx_pixel_put(img, y + xc, x + yc, color);
		my_mlx_pixel_put(img, -x + xc, y + yc, color);
		my_mlx_pixel_put(img, -y + xc, -x + yc, color);
		my_mlx_pixel_put(img, -x + xc, -y + yc, color);
		my_mlx_pixel_put(img, -y + xc, x + yc, color);
	}
}


/*
** ft_midpoint_circle function use int as variable
** is an algotithm
*/

void	ft_circle(t_data *img, int xc, int yc, int radius, int color)
{
	int x = 0;
	int y = radius;
	int h = 1 - radius;
	int i = 200;

	while (y > x)
	{
		if (h < 0)
			h = h + 2 * x +3;
		else
		{
			h = h + 2 * (x - y) + 5;
			y--;
		}
		ft_put_symmetry(img, xc, yc, x, y, color, 1);
		x++; i++;
	}
}



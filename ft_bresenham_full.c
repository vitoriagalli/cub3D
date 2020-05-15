#include "cub3d.h"

void	ft_increment_x_full(t_data *img, int x0, int y0, int x1, int y1, int dx, int dy)
{
	int x, y;
	int yl;
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
		yl = (y <= y1) ? y0 : y1;
		int i = 400;
		while (yl <= y)
		{
			my_mlx_pixel_put(img, x, yl, ft_color(i));
			yl++; i++;
		}
		my_mlx_pixel_put(img, x, y, ft_color(i));
	}
}

void	ft_increment_y_full(t_data *img, int x0, int y0, int x1, int y1, int dx, int dy)
{
	int x, y;
	int slope, yl;
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
		yl = (y <= y1) ? y0 : y1;
		int i = 0;
		while (yl <= y)
		{
			my_mlx_pixel_put(img, x, yl, ft_color(i));
			yl++; i++;
		}
		my_mlx_pixel_put(img, x, y, ft_color(i));
	}
}

void ft_line_bresenham_full(t_data *img, int x0, int y0, int x1, int y1)
{
	int 	dx;
	int 	dy;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);

	if(dx >= dy)
		ft_increment_x_full(img, x0, y0, x1, y1, dx, dy);
	else
	{
		/*
		** slope > 45°
		** o incremento é sobre y e não sobre x
		*/
		ft_increment_y_full(img, x0, y0, x1, y1, dx, dy);
	}
}

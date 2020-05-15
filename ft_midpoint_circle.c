#include "cub3d.h"

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

void	ft_midpoint_circle(t_data *img, int xc, int yc, int radius)
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
		ft_put_symmetry(img, xc, yc, x, y, ft_color(i), 1);
		x++; i++;
	}
}


void	ft_full_circle(t_data *img, int xc, int yc, int radius)
{
	double angle = 0.0;
	double x = 0;
	double y = 0;
	double r = 0;
	int col = 270;
	int color;

	while (angle < PI / 2)
	{
		r = 0;
		col++; color = ft_color(col);
		while (r < radius)
		{
			x = r * sin(angle);
			y = r * cos(angle);
			my_mlx_pixel_put(img, xc + x, yc + y, color);
			my_mlx_pixel_put(img, xc - x, yc - y, color);
			my_mlx_pixel_put(img, xc - x, yc + y, color);
			my_mlx_pixel_put(img, xc + x, yc - y, color);
			r = r + 0.01;
		}
		angle = angle + 0.005;
	}
}

void	ft_circle(t_data *img, int xc, int yc, int radius)
{
	float x = 0;
	float y = 0;

	while (x < 2 * radius)   //arrumar centro
	{
		y = sqrtf(2*radius*x - x*x);
		my_mlx_pixel_put(img, x + xc, y + yc, 0xff0000ff);
		my_mlx_pixel_put(img, xc + x, yc - y, 0xff0000ff);
		x = x + 0.001;
	}
}

#include "cub3d.h"

/*
** ft_circle function use float as variable
*/

void	ft_arc_circle(t_data *img, t_player center)
{
	float angle;
	float increase_angle = 0.01;
	int new_x;
	int new_y;

	angle = 0.0;
	while (angle < 2 * M_PI)
	{
		new_x = center.x + (center.radius * cos(angle));
		new_y = center.y + (center.radius * sin(angle));
		my_mlx_pixel_put(img, new_x, new_y, center.color);
		angle += increase_angle;
	}
}


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

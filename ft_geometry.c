#include "cub3d.h"

// demora demais
void	draw_full_circle(t_data *img)
{
	float x;
	float y = 0;
	float y2 = 0;
	int r = 150;

	while (y < r)
	{
		x = sqrtf(2*r*y - y*y);
		y2 = y;
		while (y2 < (2*r - y))
		{
			my_mlx_pixel_put(img, 200 + x, 50 + y2, 0xff0000ff);
			my_mlx_pixel_put(img, 200 - x, 50 + y2, 0xff0000ff);
			y2 = y2 + 0.05;
		}
		y = y + 0.001;
	}
}


void	draw_line(t_data *img)
{
	/*
	** por exemplo:	y = 0.5x + 10
	** p1(50,35)	m1 = 0.5 < 1
	*/
	float x;
	float y;

	x = 50;
	while (x < 300)
	{
		y = 1 * x + 10;
		my_mlx_pixel_put(img, x, y, 0xff0000ff);
		x = x + 1;
	}
}

void	draw_line_dda(t_data *img)
{
	/*
	** por exemplo:	y = 0.5x + 10
	** p1(50,35)	m1 = 0.5 < 1
	*/

	float x = 50;
	float y = 35;
	float x2 = 0;
	float y2 = 0;
	float m = 1;

	while (x2 < 300)
	{
		if (m < 1)
		{
			x2 = x + 1;
			y2 = y + m;
			my_mlx_pixel_put(img, x2, y2, 0xff0000ff);
			x = x2;
			y = y2;
		}
		else
		{
			x2 = x + 1/m;
			y2 = y + 1;
			my_mlx_pixel_put(img, x2, y2, 0xff0000ff);
			x = x2;
			y = y2;
		}
	}
}

void	draw_triangle(t_data *img)
{
	float x;
	float y;
	float m;

	x = 10;
	m = 1.9;
	while (x < 110)
	{
		y = -1* m * x + 219;
		my_mlx_pixel_put(img, x, y, 0xff0000ff);
		x = x + 1;
	}
	while (x < 210)
	{
		y = +1 * m * x - 199;
		my_mlx_pixel_put(img, x, y, 0xff0000ff);
		x = x + 1;
	}
	x = 10;
	while (x < 210)
	{
		my_mlx_pixel_put(img, x, 200, 0xff0000ff);
		x = x + 1;
	}
}

void	draw_triangle_full(t_data *img)
{
	float x;
	float y;
	float m;

	x = 10;
	m = 1.9;
	while (x < 110)
	{
		y = -1* m * x + 219;
		while (y < 200)
		{
			my_mlx_pixel_put(img, x, y, 0xff0000ff);
			y++;
		}
		x = x + 1;
	}
	while (x < 210)
	{
		y = +1 * m * x - 199;
		while (y < 200)
		{
			my_mlx_pixel_put(img, x, y, 0xff0000ff);
			y++;
		}
		x = x + 1;
	}
}

void	ft_line_bresenham_positive(t_data *img, int x1, int y1, int x2, int y2)
{
	int p, dx, dy;

	dx = x2 - x1;
	dy = y2 - y1;

	if (dy > 0)
	{
		p = 2 * dy - dx;
		while(x1 <= x2)
		{
			my_mlx_pixel_put(img, x1, y1, 0xff0000ff);
			x1++;
			if (p < 0)
				p = p + 2 * dy;
			else
			{
				p = p + 2 * dy - 2 * dx;
				y1++;
			}
		}
	}
	else
	{
		dy = dy * -1;
		while(x1 <= x2)
		{
			my_mlx_pixel_put(img, x1, y1, 0xff0000ff);
			x1++;
			if (p < 0)
				p = p + 2 * dy;
			else
			{
				p = p + 2 * dy + 2 * dx;
				y1--;
			}
		}
	}
}



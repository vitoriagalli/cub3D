#include "cub3d.h"

void	draw_circle(t_data *img)
{
	int	origin_x = 250;
	int	origin_y = 250;
	float x;
	float y = 0;
	int r = 150;

	while (y < 300)
	{
		x = sqrtf(2*r*y - y*y);
		my_mlx_pixel_put(img, 200 + x, 100 + y, 0xff0000ff);
		my_mlx_pixel_put(img, 200 - x, 100 + y, 0xff0000ff);
		y = y + 0.001;
	}
}

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


void	draw_full_circle_polar(t_data *img)
{
	double angle = 0.0;
	double x = 0;
	double y = 0;
	double r = 0;  // rmax = 100
	int	xc = 100;
	int yc = 100;
	int color;

	while (angle < PI / 2)
	{
		r = 0;
		color = 0xFFFF0000;
		while (r < 80)
		{
			x = r * sin(angle);
			y = r * cos(angle);
			my_mlx_pixel_put(img, xc + x, yc + y, color);
			my_mlx_pixel_put(img, xc - x, yc - y, color);
			my_mlx_pixel_put(img, xc - x, yc + y, color);
			my_mlx_pixel_put(img, xc + x, yc - y, color);
			r = r + 0.01;
		}
		angle = angle + 0.01;
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

void	draw_line_bresenham(t_data *img)
{
	int x1, x2, y1, y2, dx, dy, p;

	x1 = 100; x2 = 300;
	y1 = 50; y2 = 400;

	dx = x2 - x1;
	dy = y2 - y1;
	p = 2 *dy - dx;

	while(x1 < x2)
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

void	ft_bresenham(t_data *img, int x1, int y1, int x2, int y2)
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

void	draw_triangle_bresenham(t_data *img)
{
	char *data;

	data = img->addr;
	printf("%s\n", img->addr);
	ft_bresenham(img, 0, 200, 100, 0);
	ft_bresenham(img, 100, 0, 200, 100);
}

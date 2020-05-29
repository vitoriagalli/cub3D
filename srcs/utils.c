#include "cub3d.h"

double	ft_normalize_angle(double angle)
{
	angle = remainder(angle, 2 * PI);
	if (angle < 0)
		angle += (2 * PI);
	return (angle);
}

int	ray_facing(double angle, int way)
{
	int	up;
	int	down;
	int	left;
	int	right;

	down = (angle > 0 && angle < PI) ? 1 : 0;
	up = !(down) ? 1 : 0;
	left = (angle > PI / 2 && angle < 3 * PI / 2) ? 1 : 0;
	right = !left ? 1 : 0;
	if (way == RAY_UP)
		return (up);
	else if (way == RAY_DOWN)
		return (down);
	else if (way == RAY_LEFT)
		return (left);
	else if (way == RAY_RIGHT)
		return (right);
	return (-1);
}

int	is_end_window(double x, double y)
{
	if (x <= 0 || x >= WIDTH || y <= 0 || y >= HEIGHT)
		return (1);
	return (0);
}

double	dist_btw_points(double x0, double y0, double x1, double y1)
{
	return(sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
}

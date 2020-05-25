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

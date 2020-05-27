#include "cub3d.h"

void	ft_rays(t_data *img, t_player *player)
{
	double	ray_angle;
	//int		column_id;
	int 	i;
	int		x1;
	int		y1;

	//column_id = 0;
	ray_angle = player->rotation_angle - FOV / 2;
	i = 0;
	while(i < NUM_RAYS)
	{
		x1 = player->x + sin(ray_angle) * 30;
		y1 = player->y + cos(ray_angle) * 30;
		ft_line(img, player->x, player->y, x1, y1, 0x00ffff00);

		ray_angle += FOV /NUM_RAYS;
		i++;
	}
}


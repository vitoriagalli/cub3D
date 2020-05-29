#include "cub3d.h"

void	ft_fov(t_data *img, t_player *player)
{
	double	ray_angle;
	int x1; int y1;
	//int		column_id;
	int 	i;

	//column_id = 0;
	ray_angle = player->rotation_angle - FOV / 2;
	i = 0;
	while(i < NUM_RAYS)
	{
		x1 = player->x + cos(ray_angle) * 30;
		y1 = player->y + sin(ray_angle) * 30;
		ft_line(img, player->x, player->y, x1, y1, 0xff00ff00);
		ray_angle += FOV /NUM_RAYS;
		i++;
	}
}

void	put_rays(t_data *img, t_player *player)
{
	double	ray_angle;
	t_point	*intercept;
	//int		column_id;
	int 	i;

	//column_id = 0;
	ray_angle = ft_normalize_angle(player->rotation_angle - FOV / 2);
	i = 0;
	//while(i < NUM_RAYS)
	while(i < 1)
	{
		intercept = cast_ray(player, ray_angle);

		ft_line(img, player->x, player->y, intercept->x, intercept->y, intercept->color);
		ray_angle += FOV /NUM_RAYS;
		i++;
	}
	free(intercept);
}


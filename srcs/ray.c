#include "cub3d.h"

void	ft_fov(t_data *img, t_player *player)
{
	float	ray_angle;
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
		ray_angle += FOV / NUM_RAYS;
		i++;
	}
}

void	put_rays(t_data *img, t_player *player)
{
	float	ray_angle;
	t_point	*intercept;
	//int		column_id;
	int 	i;

	//column_id = 0;
	ray_angle = ft_normalize_angle(player->rotation_angle - FOV / 2);
	i = 0;
	while(i < NUM_RAYS)
	//while(i < 1)
	{
		intercept = closest_wall(player, ray_angle);

		//printf("angle = %f   distance = %f\n", ray_angle,
		//dist_btw_points(player->x, player->y, intercept->x, intercept->y));

		ft_line(img, player->x, player->y, intercept->x, intercept->y, intercept->color);
		ray_angle += FOV /NUM_RAYS;
		ray_angle = ft_normalize_angle(ray_angle);
		free(intercept);
		i++;
	}
}

//	0 -> HORIZONTAL				1 -> VERTICAL
t_point	*cast_ray(t_player *player, float ray_angle, int coord)
{
	t_point	*step;
	t_point *intercept;
	int		next_x;
	int		next_y;
	int		x_check;
	int		y_check;

	intercept = create_point();
	step = coord == 0 ?
		horiz_inters(player, intercept, ray_angle) :
		vert_inters(player, intercept, ray_angle);
	next_x = intercept->x;
	next_y = intercept->y;
	while (!is_end_window(next_x, next_y))
	{
		x_check = next_x + ((ray_facing(ray_angle, RAY_LEFT) && coord == 1) ? -1 : 0);
		x_check += ((ray_facing(ray_angle, RAY_RIGHT) && coord == 1) ? 1 : 0);
		y_check = next_y + ((ray_facing(ray_angle, RAY_DOWN) && coord == 0) ? 1 : 0);
		y_check += ((ray_facing(ray_angle, RAY_UP) && coord == 0) ? -1 : 0);

		if (is_wall(x_check, y_check))
		{
			assign_point(intercept, next_x, next_y, intercept->color);
			free(step);
			return (intercept);
		}
		else
		{
			next_x += step->x;
			next_y += step->y;
		}
	}
	free(step);
	assign_point(intercept, 0, 0, 0);
	return(intercept);  //NÃO ACHOU WALL, RETORNAR VAR VALUE
}


#include "cub3d.h"

t_point	*horizontal_intersection(t_player *player, t_point *intercept, double ray_angle)
{
	t_point	*step;

	step = create_point();
	intercept->y = floor(player->y / TILE_SIZE) * TILE_SIZE;
	intercept->y += ray_facing(ray_angle, RAY_DOWN)? TILE_SIZE : 0;
	intercept->x = player->x + (intercept->y - player->y) / tan(ray_angle);
	step->y = TILE_SIZE;
	step->y *= ray_facing(ray_angle, RAY_UP)? -1 : 1;
	step->x = TILE_SIZE / tan (ray_angle);
	step->x *= (ray_facing(ray_angle, RAY_LEFT) && step->x > 0) ? -1 : 1;
	step->x *= (ray_facing(ray_angle, RAY_RIGHT) && step->x < 0) ? -1 : 1;
	return (step);
}

t_point	*cast_ray(t_player *player, double ray_angle)
{
	t_point	*step = NULL;
	t_point	*intercept = NULL;

	int		next_horiz_x;
	int		next_horiz_y;
	int		x_check;
	int		y_check;

	intercept = create_point();
	step = horizontal_intersection(player, intercept, ray_angle);

	next_horiz_x = intercept->x;
	next_horiz_y = intercept->y;

	// caso tan seja muito grande, linha praticamente horizontal
	// REVEEEEEER ESSA JOÇA
	if (next_horiz_x + step->x > (WIDTH - TILE_SIZE)	|| intercept->x + step->x < TILE_SIZE)
	{
		intercept->x = floor(player->x % WIDTH);
		step->x = TILE_SIZE;
		step->x *= ray_facing(ray_angle, RAY_LEFT)? -1 : 1;
		step->y = 0;
	}

	while (!is_end_window(next_horiz_x, next_horiz_y))
	{
		x_check = next_horiz_x + (ray_facing(ray_angle, RAY_LEFT) ? -1 : 1);
		y_check = next_horiz_y + (ray_facing(ray_angle, RAY_DOWN) ? 1 : -1);

		if(is_wall(x_check, y_check))
		{
			intercept->x = next_horiz_x;
			intercept->y = next_horiz_y;
			break;
		}
		else
		{
			next_horiz_x += step->x;
			next_horiz_y += step->y;
		}
	}
	intercept->x = next_horiz_x;
	intercept->y = next_horiz_y;
	free(step);
	return(intercept);
}


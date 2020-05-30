/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intercep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:27 by vscabell          #+#    #+#             */
/*   Updated: 2020/05/30 17:22:22 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	*horiz_inters(t_player *player, t_point *intercept, float ray_angle)
{
	t_point	*step;

	step = create_point(0, 0, 0xFF00FF00);
	intercept->y = floor(player->y / TILE_SIZE) * TILE_SIZE;
	intercept->y += ray_facing(ray_angle, ray_down)? TILE_SIZE : 0;
	intercept->x = player->x + (intercept->y - player->y) / tan(ray_angle);
	step->y = TILE_SIZE;
	step->y *= ray_facing(ray_angle, ray_up)? -1 : 1;
	step->x = TILE_SIZE / tan (ray_angle);
	step->x *= (ray_facing(ray_angle, ray_left) && step->x > 0) ? -1 : 1;
	step->x *= (ray_facing(ray_angle, ray_right) && step->x < 0) ? -1 : 1;
	return (step);
}

t_point	*vert_inters(t_player *player, t_point *intercept, float ray_angle)
{
	t_point	*step;

	step = create_point(0, 0, 0xFF00FF00);
	// verificar necessidade
	//if (ray_angle == PI / 2  || ray_angle == 3 * PI / 2)
	//	return (NULL);
	intercept->x = floor(player->x / TILE_SIZE) * TILE_SIZE;
	intercept->x += ray_facing(ray_angle, ray_right)? TILE_SIZE : 0;
	intercept->y = player->y + (intercept->x - player->x) * tan(ray_angle);
	step->x = TILE_SIZE;
	step->x *= ray_facing(ray_angle, ray_left)? -1 : 1;
	step->y = TILE_SIZE * tan (ray_angle);
	step->y *= (ray_facing(ray_angle, ray_up) && step->y > 0) ? -1 : 1;
	step->y *= (ray_facing(ray_angle, ray_down) && step->y < 0) ? -1 : 1;
	return (step);
}

t_point	*closest_wall(t_player *player, float ray_angle)
{
	t_point	*horiz_intercept;
	t_point *vert_intercept;
	float	dist_horiz;
	float	dist_vert;

	horiz_intercept = cast_ray(player, ray_angle, 0);
	vert_intercept = cast_ray(player, ray_angle, 1);

	if (vert_intercept->color == 0)
	{
		free(vert_intercept);
		return(horiz_intercept);
	}
	else if (horiz_intercept->color == 0)
	{
		free(horiz_intercept);
		return(vert_intercept);
	}
	dist_horiz = dist_btw_points(player->x, player->y, horiz_intercept->x, horiz_intercept->y);
	dist_vert = dist_btw_points(player->x, player->y, vert_intercept->x, vert_intercept->y);

	if (dist_horiz < dist_vert)
	{
		free(vert_intercept);
		return(horiz_intercept);
	}
	else
	{
		free(horiz_intercept);
		return(vert_intercept);
	}
}

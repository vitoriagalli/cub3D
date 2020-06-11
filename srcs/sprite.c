/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 16:28:06 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/11 04:41:26 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	project_sprite(t_vars *vars)
{
	int xi;

	vars->sprite->angle = atan((vars->sprite->posit->y - vars->player->posit->y) /
	(vars->sprite->posit->x - vars->player->posit->x));

	vars->sprite->dist = dist_btw_points(vars->player->posit->x, vars->player->posit->y,
	vars->sprite->posit->x, vars->sprite->posit->y);


	vars->sprite->angle_dif = ft_normalize_angle(vars->player->rotation_angle - vars->sprite->angle);
	vars->sprite->dist *= fabs(cos(vars->sprite->angle_dif));

	//if (vars->sprite->angle_dif < FOV)
	{
		vars->sprite->height = (TILE_SIZE * vars->player->dist_proj_plane / vars->sprite->dist);
		vars->sprite->width = (vars->sprite->height * vars->tex[sprite]->width / vars->tex[sprite]->height);
		xi = tan(vars->sprite->angle) * vars->player->dist_proj_plane + (vars->map->width / 2);
		project_sprite(vars, xi);
	}

}

void	draw_sprite(t_vars *vars, int x)
{
	t_point			i;
	t_point			tex;
	t_point			start;
	unsigned int	color;

	i.x = x - vars->sprite->width / 2;
	start.x = i.x;
	while (i.x < x + vars->sprite->width / 2 && vars->sprite->posit->x)
	{
		tex.x = vars->tex[sprite]->width * (i.x - start.x) / vars->sprite->width;
		i.y = (vars->map->height / 2) - (vars->sprite->width/ 2);
		start.y = i.y;
		while (i.y < (vars->map->height / 2) + (vars->sprite->height / 2) && i.x >= 0 && i.x <= vars->map->width)
		{
			tex.y = vars->tex[sprite]->height * (i.y - start.y) / vars->sprite->height;
			if (i.x > 0 && i.x < vars->map->width && i.y > 0 && i.y < vars->map->height && vars->sprite->dist < vars->ray[(int)i.x]->dist_wall)
				((color = get_texture_color(vars->tex[sprite], tex.x, tex.y)) & 0x00FFFFFF) ? my_mlx_pixel_put(vars->data, i.x, i.y, color) : 0;
			i.y++;
		}
		i.x++;
	}
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 16:28:06 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/11 22:52:21 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	project_sprite(t_vars *vars)
{
	int i;

	i = 0;
	sort_sprite(vars);
	while (i < vars->map->n_sprites)
	{
		calculate_sprite(vars, i);
		i++;
	}
}



void	calculate_sprite(t_vars *vars, int s)
{
	int xi;

	xi = 0;

	vars->sprite[s]->angle = atan2((vars->sprite[s]->posit->y - vars->player->posit->y),
	(vars->sprite[s]->posit->x - vars->player->posit->x));

	vars->sprite[s]->angle_dif = (vars->player->rotation_angle - vars->sprite[s]->angle);

	if (vars->sprite[s]->angle_dif < -1 * PI)
	 	vars->sprite[s]->angle_dif += 2 * PI;
	if (vars->sprite[s]->angle_dif > PI)
		vars->sprite[s]->angle_dif -= 2 * PI;
	vars->sprite[s]->angle_dif = fabs(vars->sprite[s]->angle_dif);



	// vars->sprite[s]->dist = dist_btw_points(vars->player->posit->x, vars->player->posit->y,
	// vars->sprite[s]->posit->x, vars->sprite[s]->posit->y);
	vars->sprite[s]->dist *= (cos(vars->sprite[s]->angle_dif));

	if (vars->sprite[s]->angle_dif < FOV / 2)
	{
		vars->sprite[s]->height = (TILE_SIZE * vars->player->dist_proj_plane / vars->sprite[s]->dist);
		vars->sprite[s]->width = (vars->sprite[s]->height * vars->tex[sprite]->width / vars->tex[sprite]->height);

		xi = tan(vars->sprite[s]->angle - vars->player->rotation_angle) * vars->player->dist_proj_plane + (vars->map->width / 2);
		draw_sprite(vars, s, xi);
	}
}

void	draw_sprite(t_vars *vars, int s, int x)
{
	t_point			i;
	t_point			tex;
	t_point			start;
	unsigned int	color;

	i.x = x - vars->sprite[s]->width / 2;
	start.x = i.x;
	while (i.x < x + vars->sprite[s]->width / 2 && vars->sprite[s]->posit->x)
	{
		tex.x = vars->tex[sprite]->width * (i.x - start.x) / vars->sprite[s]->width;
		i.y = (vars->map->height / 2) - (vars->sprite[s]->width/ 2);
		start.y = i.y;
		while (i.y < (vars->map->height / 2) + (vars->sprite[s]->height / 2) && i.x >= 0 && i.x <= vars->map->width)
		{
			tex.y = vars->tex[sprite]->height * (i.y - start.y) / vars->sprite[s]->height;
			if (i.x > 0 && i.x < vars->map->width && i.y > 0 && i.y < vars->map->height && vars->sprite[s]->dist < vars->ray[(int)i.x]->dist_wall)
				((color = get_texture_color(vars->tex[sprite], tex.x, tex.y)) & 0x00FFFFFF) ? my_mlx_pixel_put(vars->data, i.x, i.y, color) : 0;
			i.y++;
		}
		i.x++;
	}
}

void	sort_sprite(t_vars *vars)
{
	t_sprite	*aux;
	int			i;

	i = 0;
	while (i < vars->map->n_sprites)
	{
		vars->sprite[i]->dist = dist_btw_points(
			vars->player->posit->x, vars->player->posit->y,
			vars->sprite[i]->posit->x, vars->sprite[i]->posit->y);
		i++;
	}
	i = 0;
	while (i < vars->map->n_sprites - 1)
	{
		if (vars->sprite[i]->dist < vars->sprite[i + 1]->dist)
		{
			aux = vars->sprite[i];
			vars->sprite[i] = vars->sprite[i + 1];
			vars->sprite[i + 1] = aux;
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 16:28:06 by vscabell          #+#    #+#             */
/*   Updated: 2020/07/13 20:00:25 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_end_window_3d(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width ||
		y < 0 || y >= map->height)
		return (1);
	return (0);
}

static void	draw_sprite(t_vars *vars, int s, int x0)
{
	t_point			tex;
	t_point			in;
	t_point			c;
	unsigned int	color;
	int				ray_sprite;

	in.x = x0 - vars->sprite[s]->width / 2;
	in.y = (vars->map->height / 2) - (vars->sprite[s]->height / 2);
	c.x = 0;
	while (c.x < vars->sprite[s]->width)
	{
		c.y = 0;
		tex.x = c.x * vars->tex[sprite]->width / vars->sprite[s]->width;
		ray_sprite = (in.x + c.x) / WALL_WIDTH;
		while (c.y < vars->sprite[s]->height)
		{
			tex.y = c.y * vars->tex[sprite]->height / vars->sprite[s]->height;
			if (!is_end_window_3d(vars->map, (in.x + c.x), (in.y + c.y)) &&
			vars->sprite[s]->dist < vars->ray[(int)(ray_sprite)]->dist_wall)
				(color = get_texture_color(vars->tex[sprite], tex.x, tex.y)) ?
				my_mlx_pixel_put(vars->data, in.x + c.x, in.y + c.y, color) : 0;
			c.y++;
		}
		c.x++;
	}
}

static void	calculate_sprite(t_vars *vars, int s)
{
	int xi;

	xi = 0;
	vars->sprite[s]->angle = atan2((vars->sprite[s]->posit->y - vars->player->
	posit->y), (vars->sprite[s]->posit->x - vars->player->posit->x));
	vars->sprite[s]->angle_dif = (vars->player->rotation_angle - vars->sprite[s]
	->angle);
	if (vars->sprite[s]->angle_dif < -1 * PI)
		vars->sprite[s]->angle_dif += 2 * PI;
	if (vars->sprite[s]->angle_dif > PI)
		vars->sprite[s]->angle_dif -= 2 * PI;
	vars->sprite[s]->angle_dif = fabs(vars->sprite[s]->angle_dif);
	vars->sprite[s]->dist *= (cos(vars->sprite[s]->angle_dif));
	if (vars->sprite[s]->angle_dif < FOV / 2)
	{
		vars->sprite[s]->height = (TILE_SIZE * vars->player->dist_proj_plane /
		vars->sprite[s]->dist);
		vars->sprite[s]->width = (vars->sprite[s]->height * vars->tex[sprite]->
		width / vars->tex[sprite]->height);
		xi = tan(vars->sprite[s]->angle - vars->player->rotation_angle) * vars->
		player->dist_proj_plane + (vars->map->width / 2);
		draw_sprite(vars, s, xi);
	}
}

static void	sort_sprite(t_vars *vars)
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

void		put_sprites(t_vars *vars)
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

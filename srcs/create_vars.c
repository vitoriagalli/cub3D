/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:07 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/01 03:40:16 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_point(t_point *point, int x, int y, int color)
{
	point->x = x;
	point->y = y;
	point->color = color;
}

void	assign_player(t_player *player, int move_speed, float rotation_speed)
{
	player->turn_direction = 0;				//-1 esquerda +1 direita
	player->walk_direction = 0;				//-1 p/frente   +1 p/tras
	player->move_speed = move_speed;
	player->rotation_speed = rotation_speed;
}

void	info_map_to_player(t_player *player, t_map *map)
{
	player->posit->x = map->init_posit->x;
	player->posit->y = map->init_posit->y;
	player->rotation_angle = map->rotation_angle;
}

t_player	*create_player(t_map *map, int move_speed, float rotation_speed)
{
	t_player	*player;

	player = alocate_memory(sizeof(t_player));
	player->posit = alocate_memory(sizeof(t_point));
	info_map_to_player(player, map);
	free(map->init_posit);
	assign_player(player, move_speed, rotation_speed);
	return (player);
}

t_point	*create_point(int x, int y, int color)
{
	t_point	*point;

	point = alocate_memory(sizeof(t_point));
	assign_point(point, x, y, color);
	return (point);
}

t_data	*create_image(void *mlx_ptr, t_map *map)
{
	t_data	*img;

	img = alocate_memory(sizeof(t_data));
	img->img = mlx_new_image(mlx_ptr, map->width, map->height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->size_line, &img->endian);
	return (img);
}

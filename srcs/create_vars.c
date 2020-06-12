/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:07 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/12 22:57:52 by vscabell         ###   ########.fr       */
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
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->move_speed = move_speed;
	player->rotation_speed = rotation_speed;
}

void	info_map_to_player(t_player *player, t_map *map)
{
	player->posit->x = map->init_posit->x;
	player->posit->y = map->init_posit->y;
	player->rotation_angle = map->rotation_angle;
	free(map->init_posit);
	map->init_posit = NULL;
}

t_player	*create_player(t_map *map, int move_speed, float rotation_speed)
{
	t_player	*player;

	player = allocate_memory(sizeof(t_player));
	player->posit = allocate_memory(sizeof(t_point));
	info_map_to_player(player, map);
	free(map->init_posit);
	assign_player(player, move_speed, rotation_speed);
	return (player);
}

t_point	*create_point(int x, int y, int color)
{
	t_point	*point;

	point = allocate_memory(sizeof(t_point));
	assign_point(point, x, y, color);
	return (point);
}

t_data	*create_image(void *mlx_ptr, t_map *map)
{
	t_data	*img;

	img = allocate_memory(sizeof(t_data));
	img->img = mlx_new_image(mlx_ptr, map->width, map->height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->size_line, &img->endian);
	return (img);
}

t_tex	**create_texture(void *mlx_ptr, char **path)
{
	t_tex	**texture;

	texture = allocate_memory(sizeof(t_tex *) * 5);
	texture[north] = get_texture(mlx_ptr, path[north]);
	texture[south] = get_texture(mlx_ptr, path[south]);
	texture[east] = get_texture(mlx_ptr, path[east]);
	texture[west] = get_texture(mlx_ptr, path[west]);
	texture[sprite] = get_texture(mlx_ptr, path[sprite]);
	if (!(texture[north]) || !(texture[south]) || !(texture[east]) ||
	!(texture[west]) || !(texture[sprite]))
	{
		free_tex(mlx_ptr, texture);
		return (NULL);
	}
	return (texture);
}

t_sprite	**create_sprite(t_map *map)
{
	t_sprite	**sprite;
	int			i;

	i = 0;
	sprite = allocate_memory(sizeof(t_sprite *) * map->n_sprites + 2);

	while (i < map->n_sprites)
	{
		sprite[i] = allocate_memory(sizeof(t_sprite));
		sprite[i]->posit = allocate_memory(sizeof(t_point));
		sprite[i]->posit->x = map->sprite_posit[i]->x * TILE_SIZE + TILE_SIZE / 2;
		sprite[i]->posit->y = map->sprite_posit[i]->y * TILE_SIZE + TILE_SIZE / 2;
		free(map->sprite_posit[i]);
		map->sprite_posit[i] = NULL;
		i++;
	}
	free(map->sprite_posit);
	map->sprite_posit = NULL;
	return (sprite);
}

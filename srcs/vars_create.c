/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:07 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/16 16:15:31 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player	*create_player(t_map *map, int move_speed, double rotat_speed)
{
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	player->posit = ft_calloc(1, sizeof(t_point));
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->move_speed = move_speed;
	player->rotation_speed = rotat_speed;
	player->rotation_angle = map->rotation_angle;
	assign_point(player->posit, map->init_posit->x, map->init_posit->y,
	RAYS_2D_COLOR);
	check_n_free(map->init_posit);
	return (player);
}

t_point		*create_point(int x, int y, int color)
{
	t_point	*point;

	point = ft_calloc(1, sizeof(t_point));
	assign_point(point, x, y, color);
	return (point);
}

t_data		*create_image(void *mlx_ptr, t_map *map)
{
	t_data	*img;

	img = ft_calloc(1, sizeof(t_data));
	img->img = mlx_new_image(mlx_ptr, map->width, map->height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->size_line,
	&img->endian);
	return (img);
}

t_tex		**create_texture(void *mlx_ptr, char **path)
{
	t_tex	**texture;

	texture = ft_calloc(5, sizeof(t_tex *));
	texture[north] = load_texture(mlx_ptr, path[north]);
	texture[south] = load_texture(mlx_ptr, path[south]);
	texture[east] = load_texture(mlx_ptr, path[east]);
	texture[west] = load_texture(mlx_ptr, path[west]);
	texture[sprite] = load_texture(mlx_ptr, path[sprite]);
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
	t_sprite	**spr;
	int			i;

	i = 0;
	spr = ft_calloc(map->n_sprites + 2, sizeof(t_sprite *));
	while (i < map->n_sprites)
	{
		spr[i] = ft_calloc(1, sizeof(t_sprite));
		spr[i]->posit = ft_calloc(1, sizeof(t_point));
		spr[i]->posit->x = map->sprite_posit[i]->x * TILE_SIZE + TILE_SIZE / 2;
		spr[i]->posit->y = map->sprite_posit[i]->y * TILE_SIZE + TILE_SIZE / 2;
		check_n_free(map->sprite_posit[i]);
		i++;
	}
	check_n_free(map->sprite_posit);
	return (spr);
}

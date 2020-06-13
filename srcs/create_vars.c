/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:07 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/13 02:57:17 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_n_check(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, vars->map->width,
				vars->map->height, "MAP");
	if (!(vars->tex = create_texture(vars->mlx, vars->map->path)))
		return (ft_path_error(vars));
	vars->data = create_image(vars->mlx, vars->map);
	vars->point = create_point(0, 0, 0);
	vars->player = create_player(vars->map, MOVE_SPEED, ROTAT_SPEED);
	vars->sprite = create_sprite(vars->map);
	vars->minimap = TRUE;
	return (1);
}

void		assign_point(t_point *point, int x, int y, int color)
{
	point->x = x;
	point->y = y;
	point->color = color;
}

t_player	*create_player(t_map *map, int move_speed, float rotat_speed)
{
	t_player	*player;

	player = allocate_memory(sizeof(t_player));
	player->posit = allocate_memory(sizeof(t_point));
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->move_speed = move_speed;
	player->rotation_speed = rotat_speed;
	player->posit->x = map->init_posit->x;
	player->posit->y = map->init_posit->y;
	player->rotation_angle = map->rotation_angle;
	check_n_free(map->init_posit);
	return (player);
}

t_point		*create_point(int x, int y, int color)
{
	t_point	*point;

	point = allocate_memory(sizeof(t_point));
	assign_point(point, x, y, color);
	return (point);
}

t_data		*create_image(void *mlx_ptr, t_map *map)
{
	t_data	*img;

	img = allocate_memory(sizeof(t_data));
	img->img = mlx_new_image(mlx_ptr, map->width, map->height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->size_line,
	&img->endian);
	return (img);
}

t_tex		**create_texture(void *mlx_ptr, char **path)
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
	t_sprite	**spr;
	int			i;

	i = 0;
	spr = allocate_memory(sizeof(t_sprite *) * map->n_sprites + 2);
	while (i < map->n_sprites)
	{
		spr[i] = allocate_memory(sizeof(t_sprite));
		spr[i]->posit = allocate_memory(sizeof(t_point));
		spr[i]->posit->x = map->sprite_posit[i]->x * TILE_SIZE + TILE_SIZE / 2;
		spr[i]->posit->y = map->sprite_posit[i]->y * TILE_SIZE + TILE_SIZE / 2;
		check_n_free(map->sprite_posit[i]);
		i++;
	}
	check_n_free(map->sprite_posit);
	return (spr);
}

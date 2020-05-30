/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:07 by vscabell          #+#    #+#             */
/*   Updated: 2020/05/30 17:23:38 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_point(t_point *point, int x, int y, int color)
{
	point->x = x;
	point->y = y;
	point->color = color;
}

void	assign_player(t_player *player, int x, int y, int color)
{
	player->x = x;
	player->y = y;
	player->color = color;
	player->radius = 4;
	player->turn_direction = 0;		//-1 esquerda +1 direita
	player->walk_direction = 0;		//-1 p/frente   +1 p/tras
	player->rotation_angle = 3 * PI / 2;
	player->move_speed = 10;
	player->rotation_speed = 5 * PI / 180;
}


void	*alocate_memory(int sizeof_type)
{
	void	*variable;

	if (!(variable = malloc(sizeof_type * 1)))
		return (NULL);
	return (variable);
}

t_player	*create_player(void)
{
	t_player	*player;

	player = alocate_memory(sizeof(t_player));
	assign_player(player, WIDTH / 2, HEIGHT / 2, 0xFFFF0000);
	return(player);
}

t_point	*create_point(int x, int y, int color)
{
	t_point	*point;

	point = alocate_memory(sizeof(t_point));
	assign_point(point, x, y, color);
	return(point);
}

t_data	*create_image(void *mlx_ptr)
{
	t_data	*img;

	img = alocate_memory(sizeof(t_data));
	img->img = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->size_line, &img->endian);
	return(img);
}

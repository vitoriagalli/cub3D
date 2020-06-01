/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 23:51:07 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/01 08:02:25 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_fov(t_vars *vars)
{
	float	ray_angle;
	int		length;
	int 	i;

	i = 0;
	length = 40;
	ray_angle = vars->player->rotation_angle - FOV / 2;
	while(i < vars->map->num_rays)
	{
		ft_line(vars->data,
				vars->player->posit->x * MAP2D_SCALE,
				vars->player->posit->y * MAP2D_SCALE,
				(vars->player->posit->x + cos(ray_angle) * length) * MAP2D_SCALE,
				(vars->player->posit->y + sin(ray_angle) * length) * MAP2D_SCALE,
				vars->player->posit->color);
		ray_angle += FOV / vars->map->num_rays;
		i++;
	}
}

void	ft_circle_player(t_data *img, t_player *player)
{
	int	radius;

	radius = 5;
	ft_circle(img,
			player->posit->x * MAP2D_SCALE,
			player->posit->y * MAP2D_SCALE,
			radius * MAP2D_SCALE,
			player->posit->color);
}

void	ft_direction_player(t_data *img, t_player *player)
{
	int length;

	length = 50;
	ft_line(img,
			player->posit->x * MAP2D_SCALE,
			player->posit->y * MAP2D_SCALE,
			(player->posit->x + cos(player->rotation_angle) * length) * MAP2D_SCALE,
			(player->posit->y + sin(player->rotation_angle) * length) * MAP2D_SCALE,
			player->posit->color);
}

void	put_rays(t_vars *vars)
{
	int i;


	i = 0;
	while (i < vars->map->num_rays)
	{
		ft_line(vars->data,
		vars->player->posit->x * MAP2D_SCALE,
		vars->player->posit->y * MAP2D_SCALE,
		vars->ray[i]->collision->x * MAP2D_SCALE,
		vars->ray[i]->collision->y * MAP2D_SCALE,
		vars->player->posit->color);
		i++;
	}
}

void	map2d_player(t_vars *vars)
{
	vars->player->posit->color = 0xFFFF0000;
	ft_fov(vars);
	ft_direction_player(vars->data, vars->player);
	ft_circle_player(vars->data, vars->player);
	put_rays(vars);
}

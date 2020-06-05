/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 23:51:07 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/05 04:12:24 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_circle_player(t_data *img, t_player *player)
{
	int	posit[2];
	int	radius;

	posit[HORZ] = player->posit->x * MAP2D_SCALE;
	posit[VERT] = player->posit->y * MAP2D_SCALE;
	radius = 5 * MAP2D_SCALE;
	ft_circle(img, posit, radius, player->posit->color);
}

void	put_rays(t_vars *vars)
{
	int	posit[2];
	int	collision[2];
	int i;

	i = 0;
	while (i < vars->map->num_rays)
	//while (i < 800)
	{
		posit[0] = vars->player->posit->x * MAP2D_SCALE;
		posit[1] = vars->player->posit->y * MAP2D_SCALE;
		collision[0] = vars->ray[i]->collision->x * MAP2D_SCALE;
		collision[1] = vars->ray[i]->collision->y * MAP2D_SCALE;
		ft_line(vars->data, posit, collision, vars->player->posit->color);
		i++;
	}
}

void	put_player_minimap(t_vars *vars)
{
	vars->player->posit->color = ft_rgb(255,230,0);
	// ft_fov(vars);
	// ft_direction_player(vars->data, vars->player);
	// ft_circle_player(vars->data, vars->player);
	put_rays(vars);
}

// void	ft_fov(t_vars *vars)
// {
// 	float	ray_angle;
// 	int		length;
// 	int 	i;

// 	i = 0;
// 	length = 40;
// 	ray_angle = vars->player->rotation_angle - FOV / 2;
// 	while(i < vars->map->num_rays)
// 	{
// 		ft_line(vars->data,
// 				vars->player->posit->x * MAP2D_SCALE,
// 				vars->player->posit->y * MAP2D_SCALE,
// 				(vars->player->posit->x + cos(ray_angle) * length) * MAP2D_SCALE,
// 				(vars->player->posit->y + sin(ray_angle) * length) * MAP2D_SCALE,
// 				vars->player->posit->color);
// 		ray_angle += FOV / vars->map->num_rays;
// 		i++;
// 	}
// }

// void	ft_direction_player(t_data *img, t_player *player)
// {
// 	int length;

// 	length = 50;
// 	ft_line(img,
// 			player->posit->x * MAP2D_SCALE,
// 			player->posit->y * MAP2D_SCALE,
// 			(player->posit->x + cos(player->rotation_angle) * length) * MAP2D_SCALE,
// 			(player->posit->y + sin(player->rotation_angle) * length) * MAP2D_SCALE,
// 			player->posit->color);
// }


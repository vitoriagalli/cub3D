/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 23:51:07 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/06 21:58:09 by vscabell         ###   ########.fr       */
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
	ft_circle_player(vars->data, vars->player);
	put_rays(vars);
}


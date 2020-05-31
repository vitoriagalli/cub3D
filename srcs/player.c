/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:53 by vscabell          #+#    #+#             */
/*   Updated: 2020/05/31 07:54:24 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_circle_player(t_data *img, t_player *player)
{
	ft_circle(img, player->x * MAP2D_SCALE
				, player->y * MAP2D_SCALE
				, player->radius * MAP2D_SCALE,
				player->color);
}

void	ft_line_player(t_data *img, t_player *player)
{
	int x1;
	int y1;

	x1 = player->x + cos(player->rotation_angle) * 30;
	y1 = player->y + sin(player->rotation_angle) * 30;

	ft_line(img, player->x * MAP2D_SCALE,
			player->y * MAP2D_SCALE,
			x1 * MAP2D_SCALE,
			y1 * MAP2D_SCALE,
			player->color);
}

void	put_player(t_vars *vars)
{
	float *dist_rays;

	//ft_fov(vars);
	//ft_line_player(vars->data, vars->player);
	//ft_circle_player(vars->data, vars->player);

	dist_rays = calculate_rays(vars);
	do_projection(vars, dist_rays);
}

int	move_player_press(int keycode, t_vars *vars)
{
	if(keycode == W_KEY)
		vars->player->walk_direction = +1;
	else if(keycode == S_KEY)
		vars->player->walk_direction = -1;
	else if(keycode == D_KEY)
		vars->player->turn_direction = +1;
	else if(keycode == A_KEY)
		vars->player->turn_direction = -1;
	return(new_position_player(keycode, vars));
}

int	move_player_release(int keycode, t_vars *vars)
{
	if(keycode == W_KEY)
		vars->player->walk_direction = 0;
	else if(keycode == S_KEY)
		vars->player->walk_direction = 0;
	else if(keycode == D_KEY)
		vars->player->turn_direction = 0;
	else if(keycode == A_KEY)
		vars->player->turn_direction = 0;
	return(render(vars));
}

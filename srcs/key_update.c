/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:53 by vscabell          #+#    #+#             */
/*   Updated: 2020/07/24 22:13:58 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			update_frame(t_vars *vars)
{
	put_game(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);
	return (0);
}

static void	calculate_offset_player(int keycode, t_vars *vars)
{
	t_point	next_posit;
	t_point	offset;
	int		move_step;

	move_step = vars->player->walk_direction * vars->player->move_speed;
	offset.x = (keycode == W_KEY || keycode == S_KEY) ?
		cos(vars->player->rotation_angle) * move_step :
		cos(vars->player->rotation_angle + SOUTH) * move_step;
	offset.y = (keycode == W_KEY || keycode == S_KEY) ?
		sin(vars->player->rotation_angle) * move_step :
		sin(vars->player->rotation_angle + SOUTH) * move_step;
	next_posit.x = vars->player->posit->x + offset.x;
	next_posit.y = vars->player->posit->y + offset.y;
	if (!(is_wall(vars->map, next_posit.x + offset.x, next_posit.y + offset.y,
	'1')) && !(is_wall(vars->map, next_posit.x, next_posit.y, '2')))
	{
		vars->player->posit->x = next_posit.x;
		vars->player->posit->y = next_posit.y;
	}
}

static int	new_position_player(int keycode, t_vars *vars)
{
	if (keycode == W_KEY || keycode == S_KEY ||
		keycode == A_KEY || keycode == D_KEY)
		calculate_offset_player(keycode, vars);
	else if (keycode == RIGHT_ARROW_KEY || keycode == LEFT_ARROW_KEY)
	{
		vars->player->rotation_angle +=
		vars->player->turn_direction * vars->player->rotation_speed;
		vars->player->rotation_angle =
		ft_normalize_angle(vars->player->rotation_angle);
	}
	return (update_frame(vars));
}

int			move_player_press(int keycode, t_vars *vars)
{
	if (keycode == W_KEY)
		vars->player->walk_direction = +1;
	else if (keycode == S_KEY)
		vars->player->walk_direction = -1;
	else if (keycode == D_KEY)
		vars->player->walk_direction = +1;
	else if (keycode == A_KEY)
		vars->player->walk_direction = -1;
	else if (keycode == RIGHT_ARROW_KEY)
		vars->player->turn_direction = +1;
	else if (keycode == LEFT_ARROW_KEY)
		vars->player->turn_direction = -1;
	else if (keycode == M_KEY)
		vars->minimap = vars->minimap == TRUE ? FALSE : TRUE;
	else if (keycode == ESC_KEY)
		return (clean_before_close(vars));
	return (new_position_player(keycode, vars));
}
